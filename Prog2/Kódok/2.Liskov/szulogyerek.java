public class szulogyerek {

    public static void main(String[] args) {
        Szulo osok = new Gyerek();
            osok.uzenet();
    }
    
public static class Gyerek extends Szulo{
     void uzenet(){
        System.out.print("Az uzenet, ami nem fog megerkezni.");
    }
}
public static class Szulo extends szulogyerek{
   }
}
