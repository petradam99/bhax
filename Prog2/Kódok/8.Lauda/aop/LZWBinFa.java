

import java.io.IOException;
import java.io.*;



public class LZWBinFa  {

    public LZWBinFa() {
        gyoker = new Csomopont();
        fa = gyoker;
    }
    public void push_back(char ch) {
        if (ch == '0') {
            if (fa.getBalNulla() == null) {
                Csomopont uj = new Csomopont('0');
                fa.setNullasGyermek(uj);
                fa = gyoker;
            }
            else{
                fa = fa.getBalNulla();
            }
        }
        else if (ch == '1') {
            if (fa.getJobbEgy() == null) {
                Csomopont uj = new Csomopont('1');
                fa.setEgyesGyermek(uj);
                fa = gyoker;
            } else {
                fa = fa.getJobbEgy();
            }
        }
    }
   
    public double getAtlag() {
        melyseg = atlagosszeg = atlagdb = 0;
        ratlag(gyoker);
        atlag = (double) atlagosszeg / atlagdb;
        return atlag;
    }
    public int getMelyseg() {
        melyseg = maxMelyseg = 0;
        rmelyseg(gyoker);
        return maxMelyseg - 1;
    }
    public double getSzoras() {
        atlag = getAtlag();
        szorasosszeg = 0.0;
        melyseg = atlagdb = 0;
        rszoras(gyoker);
        if (atlagdb - 1 > 0) {
            szoras = Math.sqrt(szorasosszeg / (atlagdb - 1));
        } else {
            szoras = Math.sqrt(szorasosszeg);
        }
        return szoras;
    }
    public void kiir(PrintWriter pw) {
        melyseg = 0;
        kiir(gyoker,pw);
    }
    
  class Csomopont {
       
        public Csomopont() {
            betu = '/';
            jobbEgy = null;
            balNulla = null;
        }
        public Csomopont(char ch) {
            betu = ch;
            jobbEgy = null;
            balNulla = null;
        }
        
        public void setNullasGyermek(Csomopont nulla) {
            balNulla = nulla;
        }
        public void setEgyesGyermek(Csomopont egy) {
            jobbEgy = egy;
        }
        public void setBetu(char ch) {
            betu = ch;
        }
       
        public char getBetu() {
            return betu;
        }
        public Csomopont getJobbEgy() {
            return jobbEgy;
        }
        public Csomopont getBalNulla() {
            return balNulla;
        }
        
        private char betu;
        private Csomopont jobbEgy;
        private Csomopont balNulla;
    }

    private Csomopont fa;
    private int melyseg, atlagosszeg, atlagdb;
    private double szorasosszeg;

    public void kiir(Csomopont elem,PrintWriter pw) {
        if (elem != null) {
            melyseg++;
            kiir(elem.getJobbEgy(),pw);
            for (int i = 0; i < melyseg; i++) {
                pw.print("---");
            }
            pw.print(elem.getBetu() + "(" + (melyseg - 1) + ")" + "\n");
            kiir(elem.getBalNulla(),pw);
            melyseg--;
        }
    }

    protected Csomopont gyoker;
    protected int maxMelyseg;
    protected double atlag, szoras;
    protected void rmelyseg(Csomopont elem) {
        if (elem != null) {
            melyseg++;
            if (melyseg > maxMelyseg) {
                maxMelyseg = melyseg;
            }
            rmelyseg(elem.getBalNulla());
            rmelyseg(elem.getJobbEgy());
            melyseg--;
        }
    }
    protected void ratlag(Csomopont elem) {
        if (elem != null) {
            melyseg++;
            ratlag(elem.getBalNulla());
            ratlag(elem.getJobbEgy());
            melyseg--;
            if (elem.getJobbEgy() == null && elem.getBalNulla() == null) {
                atlagdb++;
                atlagosszeg += melyseg;
            }
        }
    }
    protected void rszoras(Csomopont elem) {
        if (elem != null) {
            melyseg++;
            rszoras(elem.getJobbEgy());
            rszoras(elem.getBalNulla());
            melyseg--;
            if (elem.getJobbEgy() == null && elem.getBalNulla() == null) {
                atlagdb++;
                szorasosszeg += (melyseg - atlag) * (melyseg - atlag);
            }
        }
    }
    public static void main(String[] args) throws IOException {
     LZWBinFa binfa = new LZWBinFa();
    String str = new String();
    str="01111001"; 
    for(int i = 0; i < str.length(); i++){
            binfa.push_back(str.charAt(i));
        } 
 
    PrintWriter out =new PrintWriter(args[0]);

    binfa.kiir(out);
    out.close();
    

    }
}
