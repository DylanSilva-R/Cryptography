public class Test 
{
    public static void main(String[] args) 
    {
        int polynomial = 0b10101;

        int newVO = polynomial << 3;
        int newVT = polynomial << 1;
        int newVTh = polynomial << 0;

        System.out.println(Integer.toBinaryString(newVO));
        System.out.println(Integer.toBinaryString(newVT));
        System.out.println(Integer.toBinaryString(newVTh));

        int total = (newVO ^ newVT) ^ newVTh;

        System.out.println(Integer.toBinaryString(total));
        
    }
    
}
