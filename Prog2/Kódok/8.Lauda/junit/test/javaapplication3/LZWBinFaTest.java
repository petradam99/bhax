/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package javaapplication3;

import org.junit.Test;
import static org.junit.Assert.*;

/**
 *
 * @author nemesis
 */

/**
 *
 * @author nemesis
 */
public class LZWBinFaTest {
    LZWBinFa binfa = new LZWBinFa();
    
    String str = "0111100101100";
    
    @Test
    public void atlagTest() {
        for(int i = 0; i < str.length(); i++){
            binfa.push_back(str.charAt(i));
        }
        double atlag = binfa.getAtlag();
        assertEquals(2.25, atlag, 0.001);
    }
    @Test
    public void szorasTest() {
        for(int i = 0; i < str.length(); i++){
            binfa.push_back(str.charAt(i));
        }
        double szoras = binfa.getSzoras();
        assertEquals(0.5, szoras, 0.001);
    }
    @Test
    public void melysegTest() {
        for(int i = 0; i < str.length(); i++){
        binfa.push_back(str.charAt(i));
        }
        double melyseg = binfa.getMelyseg();
        assertEquals(3, melyseg, 0.001);
    }
}