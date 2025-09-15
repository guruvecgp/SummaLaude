import javax.jms.Connection;
import javax.jms.ConnectionFactory;
import javax.jms.Destination;
import javax.jms.MessageProducer;
import javax.jms.Session;
import javax.jms.TextMessage;
import javax.naming.Context;
import javax.naming.InitialContext;
import java.util.Hashtable;

public class JMSMQProgram.java{
    public static void main(String[] args) {
        Connection connection = null;
        Session session = null;
        MessageProducer producer = null;
	
	        try {
			Hashtable<String, String> env = new Hashtable<>();
                        env.put(Context.INITIAL_CONTEXT_FACTORY, "com.sun.jndi.fscontext.RefFSContextFactory"); // Example for file-based JNDI
                        env.put(Context.PROVIDER_URL, "file:/C:/JNDI-Directory"); // Path to your JNDI binding file	
			            Context jndiContext = new InitialContext(env);

	               // 2. Lookup ConnectionFactory and Destination (Queue)
                       ConnectionFactory connectionFactory = (ConnectionFactory) jndiContext.lookup("MyConnectionFactory"); // Your ConnectionFactory name
                       Destination queue = (Destination) jndiContext.lookup("MyQueue"); // Your Queue name
		       
		       // 3. Create Connection and Session
		       connection = connectionFactory.createConnection();
		       connection.start(); // Start the connection to enable message flow
		       session = connection.createSession(false, Session.AUTO_ACKNOWLEDGE); // false for non-transacted session, AUTO_ACKNOWLEDGE for automatic acknowledgment
											 
		       // 4. Create MessageProducer
		       producer = session.createProducer(queue);

		       // 5. Create and Send Message
		       TextMessage message = session.createTextMessage("Hello, MQ!"); // Create a text message
		       producer.send(message); // Send the message
					       
		       System.out.println("Message sent successfully!");
		       
		} catch (Exception e) {
          	       e.printStackTrace();
                } finally {
		      // 6. Close resources in finally block
		      try {
		          if (producer != null) producer.close();
		          if (session != null) session.close();
		          if (connection != null) connection.close();
		      } catch (Exception e) {
			e.printStackTrace();
		      }

		}
		
		try {
             		   if (producer != null) producer.close();
                	   if (session != null) session.close();
                	   if (connection != null) connection.close();
           	    } catch (Exception e) {
                	   e.printStackTrace();
           	    }

    }

}
