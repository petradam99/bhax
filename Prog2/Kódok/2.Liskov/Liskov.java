class Madar
{
        
    public void repul()
    {
            System.out.println("A madar repul.\n");
    }
}

class Sas extends Madar
{
    public void repul()
        {
        System.out.println("A sas repul.\n");
        }
}
class Pingvin extends Madar
{
        public void repul()
        {
        System.out.println("A pingvin valojaban nem repulhetne.\n");
        }
}

class Liskov
{

    public static void RepuloMadar(Madar b)
    {
        b.repul();
    }

    public static void main(String[] args)
    {
        Madar aSas = new Sas();
        Madar aPingvin = new Pingvin();
        
        RepuloMadar(aSas);
        RepuloMadar(aPingvin);
        
        
    }

}

