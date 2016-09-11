import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;

public class WifiTool {

    /* public PrintWriter mPrintWriterClient = null;
    public Socket mSocketClient = null;
    public BufferedReader mBufferedReaderClient	= null;
    public Thread mThreadClient = null;

	public Runnable mRunnable = new Runnable() {
        public void run() {

            String msgText ="192.168.11.245:8080";

            int start = msgText.indexOf(":");

            String sIP = msgText.substring(0, start);
            String sPort = msgText.substring(start+1);
            int port = Integer.parseInt(sPort);

            try{
                //连接服务器
                mSocketClient = new Socket(sIP, port);	//portnum
                //取得输入、输出流
                mBufferedReaderClient = new BufferedReader(new InputStreamReader(mSocketClient.getInputStream()));
                mPrintWriterClient = new PrintWriter(mSocketClient.getOutputStream(), true);
				System.out.println("klein--mPrintWriterClient" );
				System.out.println("klein--mPrintWriterClient = " + mPrintWriterClient);

            }catch (Exception e){
                e.printStackTrace();
            }

        }

    }; */
	
	
	public static void main(String[] args)
	{
/* 		WifiTool wt = new WifiTool();
		wt.mThreadClient = new Thread(mRunnable);
        wt.mThreadClient.start();

        System.out.println("klein---send data-----");
		try{
           wt.mPrintWriterClient.print("abcdefg\r\n");
           wt.mPrintWriterClient.flush();
		}catch (Exception e){
                e.printStackTrace();
            }
	} */

	 PrintWriter mPrintWriterClient = null;
     Socket mSocketClient = null;
     BufferedReader mBufferedReaderClient	= null;

     String msgText ="192.168.1.1:2001";
    //String msgText ="192.168.16.254:8080";

    int start = msgText.indexOf(":");

    String sIP = msgText.substring(0, start);
    String sPort = msgText.substring(start+1);
    int port = Integer.parseInt(sPort);

            try{
                //连接服务器
				System.out.println("klein--connecting---");
                mSocketClient = new Socket(sIP, port);	//portnum
				System.out.println("klein--connected--");
                //取得输入、输出流
                mBufferedReaderClient = new BufferedReader(new InputStreamReader(mSocketClient.getInputStream()));
                mPrintWriterClient = new PrintWriter(mSocketClient.getOutputStream(), true);
				System.out.println("klein--mPrintWriterClient");
				System.out.println("klein--mPrintWriterClient = " + mPrintWriterClient);

            }catch (Exception e){
                e.printStackTrace();
            }

	int n = 5;
	while(true)
	{
		 mPrintWriterClient.print("abcdefg\r\n");
	}
}
}