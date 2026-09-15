#!/usr/bin/env bash
# End-to-end tests for the contact book. Each case runs in a fresh temp dir,
# so the real contacts.txt is never touched.
#
#   ./test_session.sh [binary]              functional cases (default ./contactprog)
#   ./test_session.sh --valgrind [binary]   valgrind sessions (build WITHOUT sanitizers)

BIN_ARG="${1:-./contactprog}"
MODE=functional
if [ "$1" = "--valgrind" ]; then MODE=valgrind; BIN_ARG="${2:-./contactprog}"; fi
BIN=$(realpath "$BIN_ARG") || exit 2

pass=0; fail=0; info=0
ok()   { echo "PASS  $1"; pass=$((pass+1)); }
bad()  { echo "FAIL  $1"; [ -n "$2" ] && printf '%s\n' "$2" | sed 's/^/        /'; fail=$((fail+1)); }
note() { echo "NOTE  $1"; [ -n "$2" ] && printf '%s\n' "$2" | sed 's/^/        /'; info=$((info+1)); }

T=""
fresh()   { T=$(mktemp -d); cd "$T" || exit 2; }
cleanup() { cd / && chmod -R u+w "$T" 2>/dev/null; rm -rf "$T"; }
run()     { printf "$1" | "$BIN" 2>&1; }   # $1 = stdin script (printf format)

seed() {
    printf 'Ada,ada@example.com,36\nBob,bob@example.com,40\nCy,cy@example.com,50\n' > contacts.txt
}

if [ "$MODE" = valgrind ]; then
    VG="valgrind --leak-check=full --show-leak-kinds=all --error-exitcode=99"
    vg_case() { # $1 label, $2 stdin
        out=$(printf "$2" | $VG "$BIN" 2>&1)
        summary=$(printf '%s\n' "$out" | grep -E 'in use at exit|definitely|indirectly|possibly|still reachable|ERROR SUMMARY')
        if printf '%s\n' "$out" | grep -q 'All heap blocks were freed' \
           && printf '%s\n' "$out" | grep -q 'ERROR SUMMARY: 0 errors'; then
            ok "valgrind: $1"
        else
            bad "valgrind: $1" "$summary"
        fi
    }
    fresh; seed; vg_case "start, add, del, list, quit" 'add Dee,dee@example.com,22\ndel 1\nlist\nquit\n'; cleanup
    fresh; seed; vg_case "session ended by EOF (no quit)" 'add Dee,dee@example.com,22\n'; cleanup
    fresh; seed; vg_case "growth past 8 contacts" "$(for i in $(seq 1 20); do printf 'add P%d,p@x.com,%d\\n' "$i" "$i"; done)quit\n"; cleanup
    fresh; printf 'bad line\n' > contacts.txt; vg_case "startup with unparseable contacts.txt" 'quit\n'; cleanup
    echo; echo "$pass passed, $fail failed"
    exit $((fail != 0))
fi

# ---------------------------------------------------------------- persistence
fresh
out=$(run 'quit\n'); rc=$?
if [ $rc -eq 0 ]; then ok "first run with no contacts.txt starts an empty book"
else bad "first run with no contacts.txt starts an empty book" "exit $rc: $out"; fi
cleanup

fresh; : > contacts.txt
run 'add Ada,ada@example.com,36\nadd Bob,bob@example.com,40\nquit\n' >/dev/null
expected=$'Ada,ada@example.com,36\nBob,bob@example.com,40'
if [ "$(cat contacts.txt)" = "$expected" ]; then ok "add + quit writes file"
else bad "add + quit writes file" "file: $(cat contacts.txt)"; fi
out=$(run 'list\nquit\n')
if grep -q '0: Ada,ada@example.com,36' <<<"$out" && grep -q '1: Bob,bob@example.com,40' <<<"$out"
then ok "reload shows saved contacts"; else bad "reload shows saved contacts" "$out"; fi
cleanup

fresh; : > contacts.txt
run 'add Ada,ada@example.com,36\n' >/dev/null
if grep -q 'Ada' contacts.txt; then ok "EOF without quit still saves"
else bad "EOF without quit still saves" "file: $(cat contacts.txt)"; fi
cleanup

fresh; seed
run 'del 1\nquit\n' >/dev/null
if [ "$(cat contacts.txt)" = $'Ada,ada@example.com,36\nCy,cy@example.com,50' ]
then ok "del middle persists with order kept"; else bad "del middle persists with order kept" "$(cat contacts.txt)"; fi
cleanup

fresh; seed
( printf 'list\n'; sleep 2 ) | "$BIN" >/dev/null 2>&1 &
pid=$!
sleep 1
size=$(wc -c < contacts.txt)
kill -9 "$pid" 2>/dev/null; wait 2>/dev/null
if [ "$size" -gt 0 ]; then ok "contacts.txt intact while running after 'list'"
else bad "contacts.txt intact while running after 'list'" \
         "file was $size bytes after 'list' (seeded with 3 contacts); killing the process now loses them all. After kill: $(wc -c < contacts.txt) bytes"; fi
cleanup

fresh; : > contacts.txt
run 'add ,,5\nquit\n' >/dev/null
saved=$(cat contacts.txt)
out=$(run 'list\nquit\n'); rc=$?
if [ $rc -eq 0 ] && ! grep -q 'Error' <<<"$out"; then ok "add with empty name/email can't brick the file"
else bad "add with empty name/email can't brick the file" "'add ,,5' accepted, saved as '$saved'; next start: exit $rc: $out"; fi
cleanup

fresh; : > contacts.txt
run 'add Ada,a@b.com,36,junk\nquit\n' >/dev/null
if [ -s contacts.txt ]; then bad "4-field add is rejected" "'add Ada,a@b.com,36,junk' accepted -> file: $(cat contacts.txt)"
else ok "4-field add is rejected"; fi
cleanup

fresh; : > contacts.txt; chmod 444 contacts.txt
out=$(run 'list\nquit\n'); rc=$?
if [ $rc -lt 128 ] && ! grep -qE 'SEGV|AddressSanitizer' <<<"$out"; then ok "read-only contacts.txt doesn't crash 'list'"
else bad "read-only contacts.txt doesn't crash 'list'" "exit $rc: $(grep -m3 -E 'contacts.txt|SEGV|#[0-9] ' <<<"$out")"; fi
cleanup

# ---------------------------------------------------------------- input parsing
fresh; seed
out=$(run 'find Ad\nquit\n')
if grep -q '36> ' <<<"$out"; then bad "find output ends with newline" "got: $(grep -m1 36 <<<"$out")"
else ok "find output ends with newline"; fi
cleanup

fresh; seed
prefix='add Dee,d@x.com,22'
line="$prefix$(printf '%*s' $((127 - ${#prefix})) '')list"   # 127 chars fill the buffer; 'list' spills over
out=$(run "$line\\nquit\\n")
if grep -q '0: Ada' <<<"$out"; then bad "overlong line doesn't leak into next command" "a single 131-char add line also ran 'list':"$'\n'"$(grep -m2 ': ' <<<"$out")"
else ok "overlong line doesn't leak into next command"; fi
cleanup

fresh; seed
out=$(run 'del 99\ndel -1\nquit\n'); rc=$?
if [ $rc -eq 0 ] && [ "$(wc -l < contacts.txt)" -eq 3 ]; then
    if grep -qiE 'range|invalid|no such|malformed' <<<"$out"; then ok "out-of-range del is safe and reported"
    else note "out-of-range del (99, -1) is safe but silent" "output: $out"; fi
else bad "out-of-range del is safe" "exit $rc, lines left: $(wc -l < contacts.txt)"; fi
cleanup

fresh; seed
run 'del 1abc\nquit\n' >/dev/null
note "'del 1abc' -> $( [ "$(wc -l < contacts.txt)" -eq 2 ] && echo 'deleted index 1' || echo 'rejected')"
cleanup

fresh; seed
out=$(run 'find ada\nquit\n')
note "'find ada' with 'Ada' stored (spec example) -> $(grep -q 'Ada,' <<<"$out" && echo match || echo "no match: $(tr '\n' ' ' <<<"$out")")"
cleanup

fresh; seed
out=$(run 'find Zed\nquit\n')
note "'find Zed' (no such contact) prints: $(tr '\n' ' ' <<<"$out")"
cleanup

fresh; seed
out=$(run 'list please\nquit now\n'); rc=$?
note "'list please' / 'quit now' -> $(grep -q '0: Ada' <<<"$out" && echo 'list ran' || echo 'list rejected'), exit $rc"
cleanup

fresh; seed
out=$(run '\n   \nquit\n'); rc=$?
note "blank / whitespace-only lines -> exit $rc: $(tr '\n' ' ' <<<"$out")"
cleanup

echo
echo "$pass passed, $fail failed, $info notes"
exit $((fail != 0))
