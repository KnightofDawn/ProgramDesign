
public class Register_Customer extends Object implements java.io.Serializable {

	private static final long serialVersionUID = 7116984729771538742L;

	public String custName; // ����

	public String custPassword; // ����

	public String age; // ����

	public String sex; // �Ա�

	public String email; // �����ʼ�

	public String head; // ͷ���ļ���
	
	public Register_Customer() {
		// TODO Auto-generated constructor stub
	}
	
	public Register_Customer(String name, String pass, String _age,
			String _sex, String _email, String _head) {
		custName = name;
		custPassword = pass;
		age = _age;
		sex = _sex;
		email = _email;
		head = _head;
	}
}

