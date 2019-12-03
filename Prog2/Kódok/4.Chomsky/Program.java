import java.io.*;
import java.util.*;


class Lexer{
	private String text;
	public Lexer(String text)
	{
		this.text=text.toLowerCase();
	}
 
	

	private String[][] lexer=
	{
		{"α", "4", "@", "/-\\"},//a
		{"ß", "8", "|3", "|}"},//b
		{"©", "€", "¢", "{"},//c
		{"d", "|)", "|]", "|}"},//d
		{"Σ", "Œ", "3", "3"},//e
		{"╒", "|=", "£", "|#"},//f
		{"g", "6", "[", "[+"},//g
		{"♓", "4", "|-|", "[-]"},//h
		{"1", "1", "|", "!"},//i
		{"⌡", "7", "_|", "_/"},//j
		{"k", "|<", "1<", "|{"},//k
		{"l", "1", "|", "|_"},//l
		{"m", "44", "(V)", "|\\/|"},//m
		{"π", "|\\|", "/\\/", "/V"},//n
		{"σ", "0", "()", "[]"},//o
		{"p", "/o", "|D", "|o"},//p
		{"q", "9", "O_", "(,)"},//q
		{"®", "Γ", "12", "|2"},//r
		{"s", "5", "$", "$"},//s
		{"†", "╤", "τ", "'|'"},//t
		{"µ", "|_|", "(_)", "[_]"},//u
		{"v", "\\/", "\\/", "\\/"},//v
		{"w", "VV", "\\/\\/", "(/\\)"},//w
		{"x", "%", ")(", ")("},//x
		{"y", "¥", "", ""},//y
		{"z", "2", "7_", ">_"},//z
		{"Ω", "○", "º", "☺"},//0
		{"I", "I", "L", "L"},//1
		{"Z", "Z", "Z", "e"},//2
		{"E", "E", "E", "E"},//3
		{"h", "h", "A", "A"},//4
		{"S", "S", "S", "S"},//5
		{"b", "b", "G", "G"},//6
		{"T", "T", "j", "j"},//7
		{"X", "X", "X", "X"},//8
		{"g", "g", "j", "j"}//9

	};

	public String Lextext(){
		StringBuilder sb=new StringBuilder();
		String newtext;
		for(char c:text.toCharArray()){
			Random rand = new Random();
			int random = rand.nextInt(4);
			switch(c){
				case 'a':sb.append(lexer[0][random]);
				break;
				case 'b':sb.append(lexer[1][random]);
				break;
				case 'c':sb.append(lexer[2][random]);
				break;
				case 'd':sb.append(lexer[3][random]);
				break;
				case 'e':sb.append(lexer[4][random]);
				break;
				case 'f':sb.append(lexer[5][random]);
				break;
				case 'g':sb.append(lexer[6][random]);
				break;
				case 'h':sb.append(lexer[7][random]);
				break;
				case 'i':sb.append(lexer[8][random]);
				break;
				case 'j':sb.append(lexer[9][random]);
				break;
				case 'k':sb.append(lexer[10][random]);
				break;
				case 'l':sb.append(lexer[11][random]);
				break;
				case 'n':sb.append(lexer[12][random]);
				break;
				case 'm':sb.append(lexer[13][random]);
				break;
				case 'o':sb.append(lexer[14][random]);
				break;
				case 'p':sb.append(lexer[15][random]);
				break;
				case 'q':sb.append(lexer[16][random]);
				break;
				case 'r':sb.append(lexer[17][random]);
				break;
				case 's':sb.append(lexer[18][random]);
				break;
				case 't':sb.append(lexer[19][random]);
				break;
				case 'u':sb.append(lexer[20][random]);
				break;
				case 'v':sb.append(lexer[21][random]);
				break;
				case 'w':sb.append(lexer[22][random]);
				break;
				case 'x':sb.append(lexer[23][random]);
				break;
				case 'y':sb.append(lexer[24][random]);
				break;
				case 'z':sb.append(lexer[25][random]);
				break;
				case '0':sb.append(lexer[26][random]);
				break;
				case '1':sb.append(lexer[27][random]);
				break;
				case '2':sb.append(lexer[28][random]);
				break;
				case '3':sb.append(lexer[29][random]);
				break;
				case '4':sb.append(lexer[30][random]);
				break;
				case '5':sb.append(lexer[31][random]);
				break;
				case '6':sb.append(lexer[32][random]);
				break;
				case '7':sb.append(lexer[33][random]);
				break;
				case '8':sb.append(lexer[34][random]);
				break;
				case '9':sb.append(lexer[35][random]);
				break;
				default: sb.append(c);
			}
		}
		newtext=sb.toString();
		return newtext;
		
	}
	
	
}


class Program{
public static void main(String[] args) {
	while(true){
	    Scanner in = new Scanner(System.in);
	    String s = in.nextLine();
	    if(s.length()<1){
	    	break;
	    }
	    System.out.println();
	    Lexer lex=new Lexer(s);
	    System.out.println(lex.Lextext());
	    System.out.println();
	   	}
	   	
	   	
}
}
