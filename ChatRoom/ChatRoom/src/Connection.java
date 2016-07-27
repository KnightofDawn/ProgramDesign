/**
 * Title: QICQ����ϵͳ��¼���� 
 * Description: ��������� 
 * Copyright: Copyright (c) 2015
 * 
 * ��װע����Ϣ ���ڷ�������������û�����Ϣ ������Ϣ���л� �˳���Ϣ���л�
 * 
 * @author �����
 * @version 1.0
 */

import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.PrintStream;
import java.net.Socket;
import java.util.Date;
import java.util.Vector;


public class Connection extends Thread {
	private Socket netClient; // ��ͻ���ͨѶSocket

	private Vector<Customer> userOnline; // �����û��б�

	private Vector<Chat> userChat; // ������Ϣ

	private ObjectInputStream fromClient; // �ӿͻ��������� ������

	private PrintStream toClient; // �����ͻ��� ��ӡ��

	private static Vector vList = new Vector();// ע���û��б�

	private Object obj; // ��ʱ����

	private ServerFrame sFrame; // ��������־����

	@SuppressWarnings("unchecked")
	// ������ͻ���ͨѶ
	public Connection(ServerFrame frame, Socket client,
					Vector u, Vector c) {
		netClient = client;
		userOnline = u;
		userChat = c;
		sFrame = frame;
		// ����˫��ͨ��
		try {
			// �����ͻ�����
			fromClient = new ObjectInputStream(netClient.getInputStream());
			// ������д���ͻ�
			toClient = new PrintStream(netClient.getOutputStream());
		} catch (IOException e) {
			try {
				netClient.close();
			} catch (IOException e1) {
				System.out.println("���ܽ�����" + e1);
				return;
			}
		}
		this.start();
	}

	// ������ͻ��˵�ͨѶ�߳�
	public void run() {
		try {// obj��Object��Ķ���
			obj = (Object) fromClient.readObject();
			if (obj.getClass().getName().equals("Customer")) {
				serverLogin();
			} else if (obj.getClass().getName().equals("Register_Customer")) {
				serverRegiste();
			} else if (obj.getClass().getName().equals("Message")) {
				serverMessage();
			} else if (obj.getClass().getName().equals("Chat")) {
				serverChat();
			} else if (obj.getClass().getName().equals("Exit")) {
				serverExit();
			} else if (obj.getClass().getName().equals("Change_Customer")) {
				serverChange();
			}
		} catch (IOException e) {
			System.out.println(e);
		} catch (ClassNotFoundException e1) {
			System.out.println("������������" + e1);
		} finally {
			try {
				netClient.close();
			} catch (IOException e) {
				System.out.println(e);
			}
		}
	}

	@SuppressWarnings("deprecation")
	// ��¼����
	public void serverLogin() {

		try {
			Customer clientMessage = (Customer) obj;
			// ���ļ�
			FileInputStream file = new FileInputStream("user.txt");
			ObjectInputStream objInput1 = new ObjectInputStream(file);
			vList = (Vector) objInput1.readObject();
//			System.out.println("���䣺" + clientMessage.custName.toString() + 
//					" " + clientMessage.custPassword.toString());
			int find = 0; // �����жϱ�־
			// System.out.println(find);
			for (int i = 0; i < vList.size(); i++) {
				Register_Customer reg = (Register_Customer) vList.elementAt(i);
				//System.out.println(reg.custName + 
				//		" " + reg.custPassword);
				if (reg.custName.equals(clientMessage.custName)) {
					find = 1;
					if (!reg.custPassword.equals(clientMessage.custPassword)) {
						toClient.println("���벻��ȷ");
						break;
					} else {
						// �ж��Ƿ��Ѿ���¼
						int login_flag = 0;
						for (int a = 0; a < userOnline.size(); a++) {
							String _custName = ((Customer) userOnline
									.elementAt(a)).custName;
							if (clientMessage.custName.equals(_custName)) {
								login_flag = 1;
								break;
							}
						}

						if (userOnline.size() >= 50) {
							toClient.println("��¼�������࣬���Ժ�����");
							break;
						}

						if (login_flag == 0) {
							clientMessage.custHead = reg.head;// getUserHeadByName(clientMessage.custName);
							userOnline.addElement(clientMessage);
							// System.out.println("Login:"
							// + clientMessage.custName + ":"
							// + clientMessage.custHead);
							// userOnline.addElement(clientMessage.custName);
							// ���û�������
							toClient.println("��¼�ɹ�");
							Date t = new Date();
							// System.out.println("�û�" + clientMessage.custName
							// + "��¼�ɹ���" + "��¼ʱ��:" + t.toLocaleString()
							// + "\n");
							log("�û�" + clientMessage.custName + "��¼�ɹ���"
									+ "��¼ʱ��:" + t.toLocaleString() + "\n");
							freshServerUserList();
							break;
						} else {
							toClient.println("���û��ѵ�¼");
						}
					}
				} else {
					continue;
				}
			}
			if (find == 0) {
				toClient.println("û������û�������ע��");
			}

			file.close();
			objInput1.close();
			fromClient.close();
		} catch (ClassNotFoundException e) {
			System.out.println(e);
		} catch (IOException e) {
			System.out.println(e);
		}
	}

	// ˢ�·�������־���������б�
	private void freshServerUserList() {
		String[] userList = new String[50];
		Customer cus = null;
		for (int j = 0; j < userOnline.size(); j++) {
			cus = (Customer) userOnline.get(j);
			userList[j] = cus.custName;
		}
		sFrame.list.setListData(userList);
		sFrame.txtNumber.setText("" + userOnline.size());
		sFrame.lblUserCount.setText("��ǰ��������:" + userOnline.size());
		// System.out.println("fresh ok");
	}

	@SuppressWarnings({ "unchecked", "deprecation" })
	// ע�ᴦ��
	public void serverRegiste() {
		try {
			int flag = 0; // �Ƿ������жϱ�־
			Register_Customer clientMessage = (Register_Customer) obj;
			File fList = new File("user.txt");
			if (fList.length() != 0)// �ж��Ƿ��ǵ�һ��ע���û�
			{
				ObjectInputStream objInput = new ObjectInputStream(
						new FileInputStream(fList));
				vList = (Vector) objInput.readObject();
				// �ж��Ƿ�������
				for (int i = 0; i < vList.size(); i++) {
					Register_Customer reg = (Register_Customer) vList
							.elementAt(i);
					if (reg.custName.equals(clientMessage.custName)) {
						toClient.println("ע�����ظ�,������ѡ��");
						flag = 1;
						break;
					} else if (reg.custName.equals("������")) {
						toClient.println("��ֹʹ�ô�ע����,������ѡ��");
						flag = 1;
						break;
					}
				}
			}
			if (flag == 0) {
				// �����ע���û�
				vList.addElement(clientMessage);
				// �������е���д���ļ�
				FileOutputStream file = new FileOutputStream(fList);
				ObjectOutputStream objout = new ObjectOutputStream(file);
				objout.writeObject(vList);

				// ����ע��ɹ���Ϣ
				toClient.println(clientMessage.custName + "ע��ɹ�");
				Date t = new Date();
				// append("�û�"+clientMessage.custName+"ע��ɹ�!;ע��ʱ��:"+t.toLocaleString()+"\n");
				// System.out.println("�û�" + clientMessage.custName + "ע��ɹ�, "
				// + "ע��ʱ��:" + t.toLocaleString() + "\n");

				log("�û�" + clientMessage.custName + "ע��ɹ�, " + "ע��ʱ��:"
						+ t.toLocaleString() + "\n");
				file.close();
				objout.close();
				fromClient.close();
			}
		} catch (ClassNotFoundException e) {
			System.out.println(e);
		} catch (IOException e) {
			System.out.println(e);
		}
	}
	
	@SuppressWarnings({ "unchecked", "deprecation" })
	// �޸����봦��
	public void serverChange() {

		try {
			Change_Customer clientMessage = (Change_Customer) obj;
			// ���ļ�
			File fList = new File("user.txt");
			FileInputStream file = new FileInputStream(fList);
			ObjectInputStream objInput1 = new ObjectInputStream(file);
			vList = (Vector) objInput1.readObject();

			int find = 0; // �����жϱ�־
			int login_flag = 0;// �ж��Ƿ��Ѿ���¼
			Register_Customer reg = null;
			for (int i = 0; i < vList.size(); i++) {
				reg = (Register_Customer) vList.elementAt(i);

				if (reg.custName.equals(clientMessage.custName)) {
					find = 1;	// �ҵ����û������û��Ѿ�ע��
					if (!reg.custPassword.equals(clientMessage.custPassword)) {
						toClient.println("ԭ���벻��ȷ");	// ԭ�������벻��ȷ
					} else {
						vList.remove(i);
						reg.custPassword = clientMessage.newPassword;
						// �ж��Ƿ��Ѿ���¼
						for (int a = 0; a < userOnline.size(); a++) {
							String _custName = ((Customer) userOnline
									.elementAt(a)).custName;
							if (clientMessage.custName.equals(_custName)) {
								login_flag = 1;
								break;
							}
						}
					}
					break;
				}else {
					continue;
				}
			}
			file.close();
			if (find == 0) {
				toClient.println("û������û�������ע��");
			} else if(login_flag == 1) {
				toClient.println("���û��ѵ�¼�������޸�����");
			} else {
				// ����޸������û�
				vList.addElement(reg);
				// �������е���д���ļ�
				FileOutputStream file2 = new FileOutputStream(fList);
				ObjectOutputStream objout = new ObjectOutputStream(file2);
				objout.writeObject(vList);

				// ����ע��ɹ���Ϣ
				toClient.println(clientMessage.custName + "�޸�����ɹ�");
				Date t = new Date();
				// append("�û�"+clientMessage.custName+"ע��ɹ�!;ע��ʱ��:"+t.toLocaleString()+"\n");
				// System.out.println("�û�" + clientMessage.custName + "ע��ɹ�, "
				// + "ע��ʱ��:" + t.toLocaleString() + "\n");

				log("�û�" + clientMessage.custName + "�޸�����ɹ�, " + "�޸�ʱ��:"
						+ t.toLocaleString() + "\n");
			}
			objInput1.close();
			fromClient.close();
		} catch (ClassNotFoundException e) {
			System.out.println(e);
		} catch (IOException e) {
			System.out.println(e);
		}
	}

	// ������Ϣ����
	public void serverMessage() {
		try {
			Message mess = new Message(userOnline,
							userChat,
							sFrame.ti,
							"" + sFrame.serverMessage);
			// log("s:" + mess.serverMessage);
			// mess.chat = WordFilter.filter(mess.chat.get(index));

			ObjectOutputStream outputstream = new ObjectOutputStream(
					netClient.getOutputStream());
			outputstream.writeObject((Message) mess);

			// server list
			// sFrame.list.setListData(new String[] { "3", "4", "5" });
			netClient.close();
			outputstream.close();
		} catch (IOException e) {
			System.out.println(e);
		}

	}

	// ������Ϣ����
	public void serverChat() {
		// �����յ��Ķ���ֵ����������Ϣ�����л�����
		Chat cObj = new Chat();
		cObj = (Chat) obj;
		cObj.chatMessage = WordFilter.filter(cObj.chatMessage);
		chatLog(cObj);
		// ��������Ϣ�����л�������ӵ�����������Ϣ��ʸ����
		userChat.addElement((Chat) cObj);
		return;
	}

	// �û��˳�����
	@SuppressWarnings("deprecation")
	public void serverExit() {
		Exit exit = new Exit();
		exit = (Exit) obj;

		removeUser(exit);

		if (sFrame.ti.equals(exit.exitName)) {
			sFrame.ti = "";
		}

		Date t = new Date();

		log("�û�" + exit.exitName + "�Ѿ��˳�, " + 
				"�˳�ʱ��:" + t.toLocaleString() + "\n");

		freshServerUserList();
	}

	/**
	 * �����û���ɾ���˳��û�
	 * 
	 * @param exit
	 *            �˳��û�������
	 */
	private void removeUser(Exit exit) {
		// TODO �Զ����ɷ������
		Vector<Customer> vec = new Vector<Customer>();
		Customer _cus = null;
		for (int j = 0; j < userOnline.size(); j++) {
			_cus = (Customer) userOnline.get(j);
			if (!exit.exitName.equals(_cus.custName)) {
				vec.add(_cus);
			}
			// System.out.println("list:"+_cus.custName);
		}
		userOnline.removeAllElements();
		for (int j = 0; j < vec.size(); j++) {
			_cus = (Customer) vec.get(j);
			userOnline.add(_cus);
		}
		// userOnline = vec;

	}

	/**
	 * ��־����������д ��Ϣ
	 * 
	 * @param log
	 *            ��־��Ϣ
	 */
	public void log(String log) {
		String newlog = sFrame.taLog.getText() + "\n" + log;
		sFrame.taLog.setText(newlog);
	}

	/**
	 * ��־����������д���� ��Ϣ
	 * 
	 * @param obj
	 *            ���� ��Ϣ����
	 */
	@SuppressWarnings("deprecation")
	public void chatLog(Chat obj) {
		String newlog = sFrame.taMessage.getText();
		Date date = new Date();
		if (!obj.whisper) {
			newlog += "\n";
			newlog += ("[" + date.getHours() + ":" + date.getMinutes() + ":"
					+ date.getSeconds() + "]");
			newlog += obj.chatUser;
			newlog += "->";
			newlog += obj.chatToUser;
			newlog += ":";
			newlog += obj.chatMessage;
		}

		sFrame.taMessage.setText(newlog);
	}
}