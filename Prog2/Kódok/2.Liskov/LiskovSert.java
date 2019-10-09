interface Madar
{
    
}

interface Repulok extends Madar
{
    public void repul();
}
interface NemRepulok extends Madar
{
}
class Sas implements Repulok
{
    public void repul()
    {
        System.out.println("A sas repul.\n");
    }
}
class Pingvin implements NemRepulok
{
}

class LiskovSert
{

    public static void RepuloMadar(Repulok b)
    {
        b.repul();
    }

    public static void main(String[] args)
    {
        Sas aSas = new Sas();
        Pingvin aPingvin = new Pingvin();
        
        RepuloMadar(aSas);
        //RepuloMadar(aPingvin); 
        //ha ez az utolsó sor (RepuloMadar (aPingvin)) nincs kikommentelve, és aktív része a programnak akkor fordítási hiba lesz -> Liskov-elv sértése
        
        
    }

} 

