/* Ce thread remplit la meme fonction que ThreadCmdMtlbCtrl mais est
 * beaucoup plus rapide puisqu'il comprend la traduction en Java des scripts
 * getScenData, commandeVol, initCortex, getHoverPoint, saturationCommande,
 * configDrone, atterissage, decollage. Ainsi il n'y a aucun appel à Matlab qui
 * ralentirait l'execution.
 */

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.util.ArrayList;
// jna is necessary to use an external library (khepera3clib.dll)
import com.sun.jna.Native;
import com.sun.jna.Library;
import com.sun.jna.ptr.DoubleByReference;


public class ThreadCmd extends Thread {
    
    // Import of khepera3clib.dll to use the functions
    //  OpenCortex, GetDronePosition and GetWandDirection.
	public interface k3 extends Library {
		public int OpenCortex();
		public int GetDronePosition(DoubleByReference x, DoubleByReference y, DoubleByReference z, DoubleByReference x1, DoubleByReference y1, DoubleByReference z1);
		public int GetWandDirection(DoubleByReference x, DoubleByReference y, DoubleByReference z,DoubleByReference x1,DoubleByReference y1, DoubleByReference z1);
	}
    
	private InetAddress address;
	private final int portCmd = 5556, zRef = 800, altMax = 1500, yawMax = 6;
	private DatagramPacket sentData;
	private DatagramSocket socketCmd; // To send a synchronizing packet regularly
	private int size = 1024, sequenceNumber, counter; // sequenceNumber is incremented at each command sent
	private byte[] buffer = new byte [size];
	private boolean runnable;
	private final double eulerMax = 0.2;
    ArrayList<Double> errors = new ArrayList<Double>();
    // These double arrays may be modified in ArrayList for a dynamic length, it could
    // avoid to exceed index for a long flight (with 50,000, do not make a flight longer than
    // 30 or 40 seconds, it could provoke crashes ...)
    private double[] savetps = new double[50000];
    private double[][] savecmd = new double[50000][4];
    private double[][] savedrone = new double[50000][6];
    private double[][] savehover = new double[50000][3];
    k3 instance;
    
	public ThreadCmd () throws IOException {

		// Initialisation : 
        
        System.out.println("The thread who sends commands is instanciated ...");
		address = InetAddress.getByName("192.168.1.1");
		
		socketCmd = new DatagramSocket();	// On ne spécifie pas le port de connexion
		sentData = new DatagramPacket(buffer, size, address, portCmd);
		
		runnable = true;
		sequenceNumber = 0;
        counter = 0; // Compteur du nombre de boucles de commandes.
        for (int i = 0 ; i < 20000 ; i++) {
            savetps[i] = 0;
            savecmd[i][0] = 0;
            savecmd[i][1] = 0;
            savecmd[i][2] = 0;
            savecmd[i][3] = 0;
            savedrone[i][0] = 0;
            savedrone[i][1] = 0;
            savedrone[i][2] = 0;
            savedrone[i][3] = 0;
            savedrone[i][4] = 0;
            savedrone[i][5] = 0;
            savehover[i][0] = 0;
            savehover[i][1] = 0;
            savehover[i][2] = 0;
        }
        
        
		instance = (k3) Native.loadLibrary("khepera3clib.dll",k3.class);		
	}
	
	public void run () {
		
        System.out.println("The thread who sends commands starts ...");
        long debut = System.currentTimeMillis();	
		try {
			this.configDrone();
		} catch (IOException e1) {
			e1.printStackTrace();
		}
		this.decollage();
        
		while (this.getRunnable()) {
			sequenceNumber ++;
			
            savetps[counter] = (System.currentTimeMillis()-debut)/1000;
			double[][] sceneData = getSceneData();
			double[] hoverPoint = getHoverPoint(sceneData[1], zRef);
			double[] cmd = commandeVol(sceneData[0],hoverPoint);
            
            savecmd[counter] = cmd;
            savehover[counter] = hoverPoint;
            savedrone[counter] = sceneData[0];
            
			String cmdMessage = "AT*PCMD="+String.valueOf(this.sequenceNumber)+","+"1,"+arrayCmd2strCmd(cmd)+"\r";
            sentData = new DatagramPacket(cmdMessage.getBytes(), cmdMessage.length(), address, portCmd);
			try {
				socketCmd.send(sentData);
			} catch (IOException e) {
				e.printStackTrace();
			};
            counter ++;
		}
        System.out.println("The thread who sends commands is stopped ...");
		System.out.println("Number of command loops : "+counter);
    }
	
	private double[] commandeVol(double[] xPos, double[] xRef) {
		        
		double[] cmdVol = { 0 , 0 , 0 , 0 };		
		
		xPos[0] /= 1000;
		xPos[1] /= 1000;
		xPos[2] /= 1000;
		xPos[4] /= 1000;
		xPos[5] /= 1000;
        xRef[0] /= 1000;
        xRef[1] /= 1000;
        xRef[2] /= 1000;
        
		double kPitch = -0.4, kRoll = -0.4;
		int kD = -100;
		double Ex = xRef[0] - xPos[0];
		double Ey = xRef[1] - xPos[1];
		double e = Math.sqrt(Math.pow(Ex,2)+Math.pow(Ey, 2));
		double yaw = xPos[3], yawCom = Math.atan2(Ey, Ex);
		double Etta = yawCom - yaw;
		
		if (Etta > Math.PI) {
			Etta -= 2*Math.PI;
		}
		else if (Etta < -Math.PI) {
			Etta += 2*Math.PI;
		}
		errors.add(e);
        
        cmdVol[0] = kRoll * e * Math.sin(Etta);
		cmdVol[1] = kPitch * e * Math.cos(Etta);
		cmdVol[2] = 1.5*(xRef[2] - xPos[2]);
		cmdVol[3] = 0;
        
		if (errors.size() > 5) {
			int l = errors.size();
			double[] diff = { 0 , 0 , 0 , 0 , 0 };
			
            for (int j = 0 ; j < 5 ; j++) {
                diff[j] = errors.get(l-j-1) - errors.get(l-j-2);
            }
			double dd = (diff[0] + diff[1] + diff[2] + diff[3] + diff[4])/5 ;
			
			cmdVol[0] += kD * dd * Math.sin(Etta);
			cmdVol[1] += kD * dd * Math.cos(Etta);
		}
		
		for (int i = 0 ; i < 3 ; i++) {
			if (cmdVol[i] < -1) {
				cmdVol[i] = -1;
			}
			else if (cmdVol[i] > 1) {
				cmdVol[i] = 1;
			}
		}
        // In case of the drone came out of the cameras field, we make it land slowly.
        if (Double.isNaN(xPos[2]) || Double.isInfinite(xPos[2]) || xPos[2] == 0 ) {
            cmdVol[0] = 0;
            cmdVol[1] = 0;
            cmdVol[2] = -0.1;
            cmdVol[3] = 0;
        }
		//System.out.println(cmdVol[0]+","+cmdVol[1]+","+cmdVol[2]+","+cmdVol[3]+".");
		return cmdVol;
	}
    
	public double[] getHoverPoint(double[] pW, int pzRef) {
		
		double[] vDir = { pW[0] ,pW[1] , pW[2] };
		double[] point = { pW[3] ,pW[4] , pW[5] };
		double xRef, yRef;
        double k = vDir[2]/(-point[2]);
        xRef = (vDir[0]/k)+point[0];
        yRef = (vDir[1]/k)+point[1];
        // If the wand is not detected, we make the drone go in direction of the platform center.
        if ( Double.isNaN(xRef) || Double.isNaN(yRef) || Double.isInfinite(xRef) || Double.isInfinite(yRef)) {
            xRef = 0;
            yRef = 0;
        }
		double[] hoverPoint = { xRef, yRef, pzRef };
		return  hoverPoint;
	}
	public void interrupt () {
		// Interrupting the thread make the drone land.
        System.out.println("The thread who sends commands is interrupted ...");
		this.runnable = false;
		for (int i = 1 ; i < 100 ; i++) {
			sequenceNumber++;
			String atterissageStr = "AT*REF="+String.valueOf(this.getSequenceNumber())+",290717696\r";
			DatagramPacket donneesAtterissage = new DatagramPacket(atterissageStr.getBytes(), atterissageStr.length(), this.address, this.portCmd);
			try {
				this.socketCmd.send(donneesAtterissage);
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
	}
	
	public void decollage () {
		for (int i = 1 ; i < 4 ; i++) {
			sequenceNumber++;
			String decollageStr = "AT*REF="+String.valueOf(this.getSequenceNumber())+",290718208\r";
			DatagramPacket donneesDecollage = new DatagramPacket(decollageStr.getBytes(), decollageStr.length(), this.address, this.portCmd);
			try {
				this.socketCmd.send(donneesDecollage);
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
		try {
			sleep(2000);
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
	}
	
	public void configDrone () throws IOException {
		String config1, config2, config3, led, trim;
		for(int i = 0 ; i < 4 ; i++) {
			
			sequenceNumber++;
			config1 = "AT*CONFIG="+String.valueOf(this.getSequenceNumber())+",\"control:altitude_max\",\""+String.valueOf(this.altMax)+"\"\r";
			sequenceNumber++;
			led = "AT*LED="+String.valueOf(this.getSequenceNumber())+",\"control:control_yaw\",\""+String.valueOf(this.yawMax)+"\"\r";
			sequenceNumber++;
			trim = "AT*FTRIM="+String.valueOf(this.getSequenceNumber())+"\r";
			sequenceNumber++;
			config2 = "AT*CONFIG="+String.valueOf(this.getSequenceNumber())+",\"control:euler_angle_max\",\""+String.valueOf(this.eulerMax)+"\"\r";
			sequenceNumber++;
			config3 = "AT*CONFIG="+String.valueOf(this.getSequenceNumber())+",\"control:control_yaw\",\""+String.valueOf(this.yawMax)+"\"\r";
			DatagramPacket donneesConfig1 = new DatagramPacket(config1.getBytes(), config1.length(), this.address, this.portCmd);
			DatagramPacket donneesLed = new DatagramPacket(led.getBytes(), led.length(), this.address, this.portCmd);
			DatagramPacket donneesTrim = new DatagramPacket(trim.getBytes(), trim.length(), this.address, this.portCmd);
			DatagramPacket donneesConfig2 = new DatagramPacket(config2.getBytes(), config2.length(), this.address, this.portCmd);
			DatagramPacket donneesConfig3 = new DatagramPacket(config3.getBytes(), config3.length(), this.address, this.portCmd);
			this.socketCmd.send(donneesConfig1);
			this.socketCmd.send(donneesLed);
			this.socketCmd.send(donneesTrim);
			this.socketCmd.send(donneesConfig2);
			this.socketCmd.send(donneesConfig3);
			
		}
	}
	
	public double[][] getSceneData() {
		instance.OpenCortex();
		// Initialization of double pointers to send them to
		// the functions of the khepera3clib.dll library.
	    DoubleByReference X = new DoubleByReference();
	    DoubleByReference Y= new DoubleByReference();
	    DoubleByReference Z= new DoubleByReference();
	    DoubleByReference x1= new DoubleByReference();
	    DoubleByReference y1= new DoubleByReference();
	    DoubleByReference z1= new DoubleByReference();
	    DoubleByReference fX = new DoubleByReference();
	    DoubleByReference fY= new DoubleByReference();
	    DoubleByReference fZ= new DoubleByReference();
	    DoubleByReference bX= new DoubleByReference();
	    DoubleByReference bY= new DoubleByReference();
	    DoubleByReference bZ= new DoubleByReference();
	    instance.GetWandDirection(X,Y,Z,x1,y1,z1);
	    instance.GetDronePosition(fX,fY,fZ,bX,bY,bZ);
	    double[] dataDrone = { fX.getValue(),fY.getValue(),fZ.getValue(),bX.getValue(),bY.getValue(),bZ.getValue() };
	    double[] dataWand = { X.getValue(),Y.getValue(),Z.getValue(),x1.getValue(),y1.getValue(),z1.getValue() };
	    double[][] out = { dataDrone , dataWand };
	    return out;
	    
	}

	public String arrayCmd2strCmd (double[] cmd) {
		// This function convert the command from double array to string to send it
		// to the drone
		String cmdStr = String.valueOf(Float.floatToIntBits((float) cmd[0])) + ","
				+ String.valueOf(Float.floatToIntBits((float) cmd[1])) + ","
				+ String.valueOf(Float.floatToIntBits((float) cmd[2])) + ","
				+ String.valueOf(Float.floatToIntBits((float) cmd[3]));
		return cmdStr;
	}
	
    // Getters
    
    public int getSequenceNumber () {
		return this.sequenceNumber;
	}
    
    public boolean getRunnable () {
        return this.runnable;
    }
    
    public double[] getSaveTps() {
        double[] savetps2 = new double[counter];
        for (int i = 0 ; i < counter ; i++) {
            savetps2[i] = savetps[i];
        }
        return savetps2;
    }
    public double[][] getSaveDrone () {
        double[][] savedrone2 = new double[counter][6];
        for (int i = 0 ; i < counter ; i++) {
            savedrone2[i][0] = savedrone[i][0];
            savedrone2[i][1] = savedrone[i][1];
            savedrone2[i][2] = savedrone[i][2];
            savedrone2[i][3] = savedrone[i][3];
            savedrone2[i][4] = savedrone[i][4];
            savedrone2[i][5] = savedrone[i][5];
        }
        
        return savedrone2;
    }
    public double[][] getSaveHover () {
        double[][] savehover2 = new double[counter][3];
        for (int i = 0 ; i < counter ; i++) {
            savehover2[i][0] = savehover[i][0];
            savehover2[i][1] = savehover[i][1];
            savehover2[i][2] = savehover[i][2];
        }
        return savehover2;
    }
    public double[][] getSaveCmd () {
        double[][] savecmd2 = new double[counter][4];
        for (int i = 0 ; i < counter ; i++) {
            savecmd2[i][0] = savecmd[i][0];
            savecmd2[i][1] = savecmd[i][1];
            savecmd2[i][2] = savecmd[i][2];
            savecmd2[i][3] = savecmd[i][3];
        }
        return savecmd2;
    }
    
}
