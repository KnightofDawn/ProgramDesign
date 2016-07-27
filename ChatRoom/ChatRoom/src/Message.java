import java.io.Serializable;
import java.util.Vector;

public class Message implements Serializable {

	private static final long serialVersionUID = -3831507106408529855L;

	public Vector userOnLine; // �û����߶���

	public Vector chat; // ������Ϣ��

	public String ti; // ����������

	public String serverMessage;// ����
	
	public Message() {
		
	}
	
	public Message(Vector userlist, Vector chatVector,
			String dele, String announcement) {
		userOnLine = userlist;
		chat = chatVector;
		ti = dele;
		serverMessage = announcement;
	}

}