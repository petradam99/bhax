
import java.io.FileNotFoundException;
import java.io.PrintWriter;

public aspect Aspect
{


    private long egyes = 0;
    private long nullas = 0;
    pointcut pushback() : execution(public void push_back(char));
    before(char ch): pushback() && args(ch){
    if(ch == '1'){
    egyes++;
    } else {
    nullas++;
    }
    }
    pointcut main() : execution(public static void main(String[]));
    after() : main(){
    System.out.println("Egyesek száma: " + egyes);
    System.out.println("Nullások száma: " + nullas);
    }


	int depth = 0;
    
    public pointcut callKiir(LZWBinFa fa,LZWBinFa.Csomopont n, PrintWriter os):call(void LZWBinFa.kiir(LZWBinFa.Csomopont, PrintWriter))
    && args(n,os) && target(fa) && within(LZWBinFa);

    after(LZWBinFa fa,LZWBinFa.Csomopont n, PrintWriter os):callKiir(fa,n,os){


    }

	public pointcut meghiv(LZWBinFa.Csomopont n, PrintWriter os) 
	: call(void LZWBinFa.kiir(LZWBinFa.Csomopont, PrintWriter)) && args(n,os);
	
    after(LZWBinFa.Csomopont n, PrintWriter os) : meghiv(n, os)
    {   
        

        try{
        os=new PrintWriter("preorder.txt");
        preOrder(n,os);
        os.flush();
        }
        catch (FileNotFoundException e) {
            e.printStackTrace();
        }
        
    	depth = 0;
        try{
        os=new PrintWriter("postorder.txt");
    	postOrder(n,os);
        os.flush();
        
        }
        catch (FileNotFoundException e) {
            e.printStackTrace();
        }
        

    }
    
    
    public void preOrder(LZWBinFa.Csomopont n, PrintWriter p) 
    {

    	if (n != null)
        {

            ++depth;
            for (int i = 0; i < depth; ++i)
            p.print("---");
            p.print(n.getBetu () + "(" + depth + ")\n");
            preOrder (n.getBalNulla (), p);
            preOrder (n.getJobbEgy (), p);
            --depth;
        }
    }
    public void postOrder(LZWBinFa.Csomopont n, PrintWriter p) 
    {
    	if (n != null)
        {
            
            ++depth;
            postOrder (n.getBalNulla (), p);
            postOrder (n.getJobbEgy (), p);
            for (int i = 0; i < depth; ++i)
                p.print("---");
            p.print(n.getBetu () + "(" + depth + ")\n");
            --depth;
        }
    }
    
    
}
