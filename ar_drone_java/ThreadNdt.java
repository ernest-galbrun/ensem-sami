import java.net.*;
import java.nio.ByteBuffer;
import java.io.*;

public class ThreadNdt extends Thread {

	// Variables d'instances :

	private InetAddress address;
	private final static int portCmd = 5556;
	private final static int portNdt = 5554;
	private DatagramPacket receivedData;
	private DatagramSocket socketNdt; // Socket de réception des nav data
	private DatagramSocket socketCmd; // Socket d'nevoi des commandes pour la synchronisation régulière
	private FileWriter fileWriter;
	private BufferedWriter output;
	private int size = 1024;
	private int seqNum = 1; // sequence number incrementé à chaque envoi de commande
	private byte[] buffer = new byte [size];
	private long start;
	private int bat;
    private long alt;
	private float tta, phi, psi, vx, vy, vz;
    private boolean runnable;

	public ThreadNdt () throws SocketException, Exception {

		// Initialisation : 
        System.out.println("The thread who receives data is instanciated ...");
        
		address = InetAddress.getByName("192.168.1.1");
		System.out.println("\n\tDrone IP adress : "+address.toString());
		socketNdt = new DatagramSocket();
		socketCmd = new DatagramSocket();
		receivedData = new DatagramPacket(buffer, size, address, portNdt);
		String adressedufichier = "C:/Users/Khepera/Documents/MATLAB/ar_drone" +"/"+ "navdata.txt";
		System.out.println("\n\n\tPath to navdata file : "+adressedufichier+"\n\n");
		fileWriter = new FileWriter(adressedufichier,false);
		output = new BufferedWriter(fileWriter);
		
		start = System.currentTimeMillis();
		bat = 0;
		alt = 0;
		tta = 0;
		phi = 0;
		psi = 0;
		vx = 0;
		vy = 0;
		vz = 0;
        
        runnable = true;
	}

	public void run () {
		System.out.println("The thread who receives data started...");
        try {
            sleep(500);
        } catch (InterruptedException e3) {
            e3.printStackTrace();
        }
		// Creation of the packet containing 1 as int8
		ByteBuffer b = ByteBuffer.allocate(1);
		b.put(0,(byte)1);
		byte[] result = b.array();
		DatagramPacket pcktb1 = new DatagramPacket(result, result.length, address, portNdt);
		try {
			socketNdt.setSoTimeout(1000);
			socketCmd.setSoTimeout(100);
		} catch (SocketException e1) {
			e1.printStackTrace();
		}
        // To be sure that the packets are sent at least once ...
        for (int i = 0 ; i < 10 ; i++ ) {
            try {
                // We have to send 1 as int32 to initialize communication with the drone.
                socketNdt.send(pcktb1);
            } catch (IOException e2) {
                System.out.println("Echec envoi premier bit");
                e2.printStackTrace();
            }
        
            try {
                sleep(10);
            } catch (InterruptedException e1) {
                e1.printStackTrace();
            }
            // Configuration pour l'envoi regulier des donnees
            String ndtTrue = "AT*CONFIG=1,\"general:navdata_demo\",\"TRUE\"\r";
            DatagramPacket dataNdtTrue = new DatagramPacket(ndtTrue.getBytes(), ndtTrue.length(), address, portCmd);

            try {
                socketCmd.send(dataNdtTrue);
            } catch (IOException e1) {
                e1.printStackTrace();
            }
        }

		this.setStart();
		while (this.getRunnable()) {
			try {
				// Sending watchdog to synchronize

				String sync = "AT*COMWDG\r";
				DatagramPacket watchdogData = new DatagramPacket(sync.getBytes(), sync.length(), address, portCmd);
				socketCmd.send(watchdogData);

				// Receiving and converting receivedData to hexadecimal format
				socketNdt.receive(receivedData);
				StringBuilder sb = new StringBuilder();
				for (byte b1 : receivedData.getData()) {
					sb.append(String.format("%02X ", b1));
				}

				// Treating receivedData

				if (sb.length() >= 500 ) {
					this.setBattery(Integer.parseInt( new String(sb.substring(81,83)+sb.substring(78,80)+sb.substring(75,77)+sb.substring(72,74)), 16 ));
					this.setTheta(hex2float(new String(sb.substring(93,95)+sb.substring(90,92)+sb.substring(87,89)+sb.substring(84,86)))/1000);
					this.setPhi(hex2float(new String(sb.substring(105,107)+sb.substring(102,104)+sb.substring(99,101)+sb.substring(96,98)))/1000);
					this.setPsi(hex2float(new String(sb.substring(117,119)+sb.substring(114,116)+sb.substring(111,113)+sb.substring(108,110)))/1000);
					this.setAltitude(Long.parseLong( new String(sb.substring(129,131)+sb.substring(126,128)+sb.substring(123,125)+sb.substring(120,122)), 16 ));
					this.setVx(hex2float(new String(sb.substring(141,143)+sb.substring(138,140)+sb.substring(135,137)+sb.substring(132,134))));
					this.setVy(hex2float(new String(sb.substring(153,155)+sb.substring(150,152)+sb.substring(147,149)+sb.substring(144,146))));
					this.setVz(hex2float(new String(sb.substring(165,167)+sb.substring(162,164)+sb.substring(159,161)+sb.substring(156,158))));
                    
					String text = String.valueOf(System.currentTimeMillis() - start)+" "+String.valueOf(this.getBattery())+" "+String.valueOf(this.getTheta())
							+" "+String.valueOf(this.getPhi())+" "+String.valueOf(this.getPsi()) +" "+String.valueOf(this.getAltitude())
							+" "+String.valueOf(this.getVx())+" "+String.valueOf(this.getVy())+" "+String.valueOf(this.getVz())+"\n";
					output.write(text);
					output.flush();
				}

			} catch (SocketTimeoutException ste) {
                // In case of fail in receiving data, this thread stop.
                // To avoid this, we can delete "break;".
				System.out.println("Delay for receiving data is exceeded");
                System.out.println("\nThe reception of data failed, check out the connection or the drone state.\n\n");
                break;

			} catch (Exception e) {
				e.printStackTrace	();
			}
		}
		System.out.println("The thread who receives data is stopped.");
        // Trying to close navdata.txt where we put all received data.
		try {
			output.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
		return;
	}

	public float hex2float (String hexNumber) {
		// Converting data from 32 hexadecimal number format to single precision float number
		// according IEEE-754 format.
		Long inter = Long.parseLong(hexNumber,16);
		Float floatValue = Float.intBitsToFloat(inter.intValue());
		return floatValue;
	}
    
    // Getters et Setters des navdata.
    
    public long getStart() {
		return this.start;
	}
	public int getBattery() {
		return this.bat;
	}
	public float getTheta() {
		return this.tta;
	}
	public float getPhi() {
		return this.phi;
	}
	public float getPsi() {
		return this.psi;
	}
	public long getAltitude() {
		return this.alt;
	}
	public float getVx() {
		return this.vx;
	}
	public float getVy() {
		return this.vy;
	}
	public float getVz() {
		return this.vz;
	}
    
    public void setStart() {
		this.start = System.currentTimeMillis();
	}
	public void setBattery(int p) {
		this.bat = p;
	}
	public void setTheta(float p) {
		this.tta = p;
	}
	public void setPhi(float p) {
		this.phi = p;
	}
	public void setPsi(float p) {
		this.psi = p;
	}
	public void setAltitude(long p) {
		this.alt = p;
	}
	public void setVx(float p) {
		this.vx = p;
	}
	public void setVy(float p) {
		this.vy = p;
	}
	public void setVz(float p) {
		this.vz = p;
	}
    public boolean getRunnable() {
		return this.runnable;
	}
	public void interrupt() {
        
        System.out.println("The thread who receives data is interrupted ...");
		this.runnable = false;
	}
    public String toString() {
		return "Instance of Thread1\nTemps : "+String.valueOf(System.currentTimeMillis() - this.getStart())+" Battery : "+String.valueOf(this.getBattery())
        +" Theta : "+String.valueOf(this.getTheta())+" Phi : "+String.valueOf(this.getPhi())+" Psi : "+String.valueOf(this.getPsi())
        +" Altitude : "+String.valueOf(this.getAltitude())
		+" Vx : "+String.valueOf(this.getVx())+" Vy : "+String.valueOf(this.getVy())+" Vz : "+String.valueOf(this.getVz())+"\n";
	}
}
