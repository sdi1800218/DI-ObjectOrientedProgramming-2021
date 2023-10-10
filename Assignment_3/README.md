## Assignment 3: Creature Society

- sdi1800218
- HP

## Execution Instructions
- Για τη μεταγλώττιση του προγράμματος χρησιμοποιείστε: `make`, έπειτα μπορείτε
    να εκτελέσετε το binary `froutopia` μέσω: `./froutopia` και δίνοντας τα 4 δικά σας ορίσματα.
- Για μια αυτόματη εκτέλεση με το δικό μου κύρια testcase μπορείτε να τρέξετε: `make run`.
- Για το καθαρισμό από τα object και τα binaries: `make clean`.

### Example Testcases

- 5 5 5 5 5
- 5 50 3 3 3
- 10 1500 3 5 5

## Implementation Analysis

- Για τη σωστη λειτουργια του `creature` constructor, η parameterized version του περνιέται στο initializer list των parameterized conctructors των good και bad creature, ωστε να μη γινει ποτέ η κλήση στο default.

- Δεν χρεισιμοποιήθηκε CRTP για το cloning process για λόγους απλότητας της υλοποίησης.

- Εγραψα δικό μου copy constructor, αλλά του g++ ήταν πιο ακριβες, όπως φαίνεται στα σημεία `creature.cc:88` και `91`.

- Δεν ακολουθείται καμία από τις δύο προτάσεις όσον αφορα τη συνδεση μεταξύ `*creature` object instances και `creature_society` instance. Κατά τη δημιουργία των creatures δίνεται ένας pointer και το index του creature στον constructor.

### Προβλήματα σε σχέση με την υλοποίηση:

- Στο `clone()` function δεν γίνεται διαγραφή του προηγούμενου creature, αλλά overwrite.