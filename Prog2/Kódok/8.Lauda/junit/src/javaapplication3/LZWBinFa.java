/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package javaapplication3;

import java.io.IOException;

/**
 *
 * @author nemesis
 */



public class LZWBinFa {

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
    public void kiir() {
        melyseg = 0;
        kiir(gyoker);
    }
    
    private class Csomopont {
       
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

    private void kiir(Csomopont elem) {
        if (elem != null) {
            melyseg++;
            kiir(elem.getJobbEgy());
            for (int i = 0; i < melyseg; i++) {
                System.out.print("---");
            }
            System.out.print(elem.getBetu() + "(" + (melyseg - 1) + ")" + "\n");
            kiir(elem.getBalNulla());
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
        
    }
}
