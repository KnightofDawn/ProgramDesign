
public class Customer extends Object implements java.io.Serializable {

	private static final long serialVersionUID = -9215977405584592618L; // �汾����

	public String custName; // �û���

	public String custPassword; // ����

	public String custHead; // �û�ͷ��
	
	public Customer() {
		// TODO Auto-generated constructor stub
	}
	
	public Customer(String name, String pass, String head) {
		custName = name;
		custPassword = pass;
		custHead = head;
	}
}