## Assignment 4: Artifact Auction

- sdi1800218
- HP

## Execution Instructions
- Για τη μεταγλώττιση του προγράμματος χρησιμοποιείστε: `make`, έπειτα μπορείτε
    να εκτελέσετε το bytecode `Auction` μέσω: `java Auction` και δίνοντας τα 3 δικά σας ορίσματα.
- Για μια αυτόματη εκτέλεση με το δικό μου testcase μπορείτε να τρέξετε: `make run`.
- Για το καθαρισμό από τα object classes: `make clean`.

### Example Testcases

- 10 expressionism bad
- 1000 naturalism good
- 10000 impressionism excellent

## Implementation Analysis
- Τα classes `Artifact` και `Masterpiece` έχουν υλοποιηθεί ως abstract προκειμένου η υλοποίηση της `evaluate()` per derived class να είναι callable.

- Υπάρχουν `enum`s για τα Movement, Condition, Material και Technique τα οποία φέρουν μεθόδους ανάκτησης μιας τυχαίας τιμής. Μόνο το `Condition enum` έχει αντιστοιχιθεί σε αριθμητικές τιμές για λόγους σύγκρισης στην evaluate().

- Η υλοποιήση της evaluate() στα `Sculpture` και `Painting` έκαστα είναι overloaded για να λαμβάνεται υπ'όψιν το default value στο Condition parameter. Overloaded γιατί στην Java δεν υπάρχουν default values στα parameters.


### Προβλήματα σε σχέση με την υλοποίηση:

- Τα σχόλια θα μπορούσαν να είναι περισσότερα; αλλά ο κώδικας είναι σχετικά απλός.
- Δεν υπάρχει sanitization (σοβαρό) στο input.