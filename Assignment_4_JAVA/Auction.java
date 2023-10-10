import java.util.Random;

class Auction {

///////////////////////////////////////////////////////////////////////////////
    enum Condition {
        bad(0), good(1), excellent(2);

        private final int value;

        private Condition(int value) {
            this.value = value;
        }

        public int getValue() {
            return value;
        }

        public static Condition random() {
            Random rand = new Random();
            int result = rand.nextInt(3);
            if (result == 0)
                return Condition.bad;
            else if(result == 1)
                return Condition.good;
            else
                return Condition.excellent;
        }
    };

    enum Movement {
        expressionism, impressionism, naturalism;

        public static Movement random() {
            Random rand = new Random();
            int result = rand.nextInt(3);
            if (result == 0)
                return Movement.expressionism;
            else if(result == 1)
                return Movement.impressionism;
            else
                return Movement.naturalism;
        }
    };

    enum Technique {
        oil, aquarelle, tempera;

        public static Technique random() {
            Random rand = new Random();
            int result = rand.nextInt(3);
            if (result == 0)
                return Technique.oil;
            else if(result == 1)
                return Technique.aquarelle;
            else
                return Technique.tempera;
        }
    };

    enum Material {
        iron, stone, wood;

        public static Material random() {
            Random rand = new Random();
            int result = rand.nextInt(3);
            if (result == 0)
                return Material.iron;
            else if(result == 1)
                return Material.stone;
            else
                return Material.wood;
        }
    };

///////////////////////////////////////////////////////////////////////////////
    /* Artifact Class, members|contructor|methods */
    public static abstract class Artifact {
        int index;
        int year;
        String creator;

        Artifact(int ind, int yr, String crea) {
            /* Constrecteur */
            System.out.println("[Artifact::Artifact] Creating an instance of Artifact");
            index = ind;
            year = yr;
            creator = crea;
        }

        // It's like a virtual, makes it callable
        abstract Boolean evaluate(Movement m, Condition c);

        void getInfo() {
            System.out.print("This Artifact's info is:\nCreator:\t" + creator);
            System.out.print("\nYear:\t\t" + year + "\n");
        }
        void getIndex() {
            System.out.println("Artifact Index:\t" + index);
        }
    }

///////////////////////////////////////////////////////////////////////////////
    /* Masterpiece Class, members|contructor|methods */
    public static abstract class Masterpiece extends Artifact {
        Movement mov;
        Condition cond;

        Masterpiece(int _index, int _year, String _creator, Movement m, Condition c) {
            /* Constrecteur */
            super(_index, _year, _creator); // base class parameterized constructor
            System.out.println("\t[Masterpiece::Masterpiece] Creating an instance of Masterpiece");
            mov = m;
            cond = c;
        }

        //abstract Boolean evaluate();

        void getInfo() {
            super.getInfo();
            System.out.println("\t~~~~~~~MASTERPIECE~~~~~~~~");
            System.out.println("\tMovement:\t" + mov);
            System.out.println("\tCondition:\t" + cond);
        }
    }

///////////////////////////////////////////////////////////////////////////////
    /* Painting Class, members|contructor|methods */
    public static class Painting extends Masterpiece {
        int length;
        int width;
        Technique tech;

        Painting(int _index, int _year, String _creator, Movement _m, Condition _c, int len, int wid, Technique t) {
            /* Constrecteur */
            super(_index, _year, _creator, _m, _c); // base class parameterized constructor
            System.out.println("\t\t[Painting::Painting] Creating an instance of Painting");
            length = len;
            width = wid;
            tech = t;
        }

        void getInfo() {
            super.getInfo();
            System.out.println("\t\t~~~~~~~~~PAINTING~~~~~~~~");
            System.out.println("\t\tSurface:\t" + (length * width));
        }

        Boolean evaluate(Movement m) {
            // Overloading
            Condition cond = Condition.good;
            return evaluate(m, cond);
        }

        Boolean evaluate(Movement m, Condition c) {
            // Standard
            if ( (this.mov == m) &&
                ( (this.cond.getValue() >= c.getValue())
                && this.cond.getValue() >= Condition.good.getValue() )
            )
                return true;
            else
                return false;
        }
    }

///////////////////////////////////////////////////////////////////////////////
    /* Sculpture Class, members|contructor|methods */
    public static class Sculpture extends Masterpiece {
        int volume;
        Material mat;

        Sculpture(int _index, int _year, String _creator, Movement _m, Condition _c, int vol, Material m) {
            /* Constrecteur */
            super(_index, _year, _creator, _m, _c); // base class parameterized constructor
            System.out.println("\t\t[Sculpture::Sculpture] Creating an instance of Sculpture");
            volume = vol;
            mat = m;
        }

        void getInfo() {
            super.getInfo();
            System.out.println("\t\t~~~~~~~~SCULPTURE~~~~~~~~");
            System.out.println("\t\tVolume: \t" + volume);
            System.out.println("\t\tMaterial:\t" + mat);
        }

        Boolean evaluate(Movement m) {
            // Overloading
            Condition cond = Condition.excellent;
            return evaluate(m, cond);
        }

        //@Override
        Boolean evaluate(Movement m, Condition c) {
            //Default
            if ( (this.mov == m) &&
                ( (this.cond.getValue() >= c.getValue())
                && this.cond.getValue() >= Condition.excellent.getValue() )
            )
                return true;
            else
                return false;

        }
    }
///////////////////////////////////////////////////////////////////////////////

    static void auction(Artifact[] art, Movement m, Condition c) {
        /* Simulates an Auction action given a number of Artifacts */
        for (int artifac = 0; artifac < art.length; ++artifac) {

            System.out.println("\n[AUCTION] New Artifact Evaluation!");

            art[artifac].getIndex();                                // Objective 1
            art[artifac].getInfo();                                 // Objective 2
            if ( art[artifac].evaluate(m, c) )                         // Objective 3
                System.out.println("[AUCTION] Artifact PASSES evaluation!");
            else
                System.out.println("[AUCTION] Artifact FAILS evaluation!") ;

            System.out.println("");
        }
    }
    public static void main(String[] args) {

        int N;
        Movement M = null;
        Condition C = null;
        String help;

        if (args.length != 3) {
            System.out.println("Wrong number of arguments");
            System.exit(-1);
        }

        // Parse N
        N = Integer.parseInt(args[0]);

        // Parse Movement
        help = args[1];
        switch(help) {
            case "expressionism":
                M = Movement.expressionism;
                break;
            case "naturalism":
                M = Movement.naturalism;
                break;
            case "impressionism":
                M = Movement.impressionism;
                break;
        }

        // Parse Condition
        help = args[2];
        switch(help) {
            case "bad":
                C = Condition.bad;
                break;
            case "good":
                C = Condition.good;
                break;
            case "excellent":
                C = Condition.excellent;
                break;
        }

        Artifact[] Arts = new Artifact[N];
        Random rand = new Random();
        for (int index = 0; index < N; index++) {
            // Painting
            if (rand.nextInt(2) == 0) {
                Arts[index] = new Painting(index+1, rand.nextInt(2022),
                 new String("Creator" + rand.nextInt(100)), //creator
                 Movement.random(), Condition.random(),     // mc
                 rand.nextInt(1000), rand.nextInt(1000), Technique.random()
                );
            }
            // Sculpture
            else {
                Arts[index] = new Sculpture(index+1, rand.nextInt(2022),
                 new String("Creator" + rand.nextInt(100)),
                 Movement.random(), Condition.random(),
                 rand.nextInt(1000), Material.random()
                );
            }
        }

        // Make the auction happen
        auction(Arts, M, C);
    }
}