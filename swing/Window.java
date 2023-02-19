import javax.swing.* ;
import java.awt.* ;
import java.awt.event.* ;

import java.io.IOException ;
import java.net.UnknownHostException ;

import java.io.BufferedReader;
import java.io.FileReader;

public class Window extends JFrame implements ActionListener {

    private static final long serialVersionUID = 1L ;
    
    JButton alpha  ; // play a multimedia
    JButton beta ; // print a multimedia 
    JButton gamma ; // exit
    
    JTextArea textArea ;
    JScrollPane scrollBar ;
    JMenuBar menuBar ;
    JToolBar toolBar ;
    
    JMenu groupMenu ;
    JMenu multimediaMenu ;
    
    JMenuItem printGroup ;
    JMenuItem playMultimedia ;
    JMenuItem printMultimedia ;
    
    Client client ;

    public Window() throws UnknownHostException, IOException{
        this.setTitle("set-TOP box") ;
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE) ; // La fermeture de l'interface entraîne la fermeture de l'application
        this.setLayout(new BoxLayout(this.getContentPane(), BoxLayout.Y_AXIS)) ;
  
        /*
        add(alpha = new JButton("alpha")) ;
        add(beta = new JButton("beta")) ;
        add(label) ;
        alpha.addActionListener(this) ;
		*/
        
        menuBar = new JMenuBar() ;
        toolBar = new JToolBar() ;
        groupMenu = new JMenu("Group") ;
        multimediaMenu = new JMenu("Multimedia") ;
  
        printGroup = new JMenuItem("Print attributes") ;
        printGroup.addActionListener(this) ;
        playMultimedia = new JMenuItem("Play") ;
        playMultimedia.addActionListener(this) ;
        printMultimedia = new JMenuItem("Print attributes") ;
        printMultimedia.addActionListener(this) ;
   
        groupMenu.add(printGroup) ;
        multimediaMenu.add(playMultimedia) ;
        multimediaMenu.add(printMultimedia) ;
        
        menuBar.add(groupMenu) ;
        menuBar.add(multimediaMenu) ;
        this.add(toolBar, BorderLayout.NORTH) ;
        this.setJMenuBar(menuBar) ;
        
        alpha = new JButton("Play") ;
        this.add(alpha, BorderLayout.EAST) ;
        beta = new JButton("Print attributes") ;
        this.add(beta, BorderLayout.WEST) ;
        gamma = new JButton("Exit") ;
        this.add(gamma, BorderLayout.PAGE_END) ;
        
        alpha.addActionListener(this) ;
        beta.addActionListener(this) ;
        gamma.addActionListener(this) ;
        
        textArea = new JTextArea(10, 0) ;
        this.add(textArea, BorderLayout.CENTER) ;
        
        scrollBar = new JScrollPane(textArea) ;
        this.add(scrollBar) ;
        
        client = new Client(Client.DEFAULT_HOST, Client.DEFAULT_PORT) ;
              
        pack() ;
        this.setVisible(true) ;
        
    }
    
    @Override
    public void actionPerformed(ActionEvent e) {
    	String request = null;
    	JTextField toPlay = new JTextField() ; // Pour récupérer le nom de group à jouer
    	Object[] message = {"Please enter the name of the multimedia or group for your desired action, sir :", toPlay} ;
    	
    	if (e.getSource() == alpha || e.getSource() == playMultimedia) { request = "play " ; }
    	
    	else if (e.getSource() == beta || e.getSource() == printMultimedia) { request = "print " ; }
    	
    	else if (e.getSource() == printGroup) { request = "print_group " ;}
    	
    	else if (e.getSource() == gamma) { 
    		request = "stop" ;
    		System.exit(0);
        } 
    	
    	
    	int pane = JOptionPane.showConfirmDialog(null, message, "Action", JOptionPane.OK_CANCEL_OPTION) ;
        String name = toPlay.getText() ;
  		String response = client.send(request + name) ;
     	//textArea.setText(textArea.getText() + response + "\n");
  		
  		textArea.append(response + "\n");
 
    }
    
}
