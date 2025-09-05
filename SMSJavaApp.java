import com.twilio.Twilio;
import com.twilio.rest.api.v2010.account.message;
import com.twilio.type.PhoneNumber;

public class SmsSender{
	public static final String ACCOUNT_ID = "ACCXXXX";
	public static final String AUTH_TOKEN = "your_auth_token";

	public static void main(String[] args){
		Twilio.init(ACCOUNT_ID,AUTH_TOKEN);

		String toPhone = "9940078952";
		String fromPhone = "8842078952";
		String messageBody = "Hello From Java";

		try{
			Message message = Message.creator(
			new PhoneNumber(toPhone);
			new PhoneNumber(fromPhone),
			messageBody
					).create();

		System.out.println("Message SID:" + message.getSid());
		System.out.println("Message sent successfully");
		} catch (Exception e) {
		  System.err.println("Error sending SMS");
		}

}
