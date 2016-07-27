import javax.swing.*;

import java.awt.*;
import java.awt.event.*;
import java.net.*;
import java.io.*;

/**
 * Title: QICQ����ϵͳ��¼���� 
 * Description: ����ָ���ķ�������ַ���û����������޸�ԭ����
 * Copyright: Copyright (c) 2015
 * 
 * @author �����
 * @version 1.0
 */

public class ChangePass extends JFrame implements ActionListener {
	private static final long serialVersionUID = -8965773902046088264L;
	
	private JPanel pnlChange;
	
	private JLabel lblUserName, lblPassword, lblNewPassword, lblConfirmNewPass;
	
	private JLabel lblLogo;
	
	private JButton btnSubmit, btnClear, btnCancel;
	
	private JTextField txtUserName;
	
	private JPasswordField pwdPassword, pwdNewPassword, pwdConfirmNewPass;
	
	private String strServerIp;
	
	// ���ڽ��������ڶ�λ
	private Dimension scrnsize;
	private Toolkit toolkit = Toolkit.getDefaultToolkit();

	// ���췽��
	@SuppressWarnings(value={"unchecked", "rawtypes"})
	public ChangePass(String ip) {
		super("[QICQ]�������޸�����");
		strServerIp = ip;
		pnlChange = new JPanel();
		this.getContentPane().add(pnlChange);
		
		btnSubmit = new JButton("�ύ(S)");
		btnSubmit.setToolTipText("�ύ�����޸ģ����ص�¼����");
		btnSubmit.setMnemonic('S');
		btnClear = new JButton("���(L)");
		btnClear.setToolTipText("����޸���Ϣ");
		btnClear.setMnemonic('L');
		btnCancel = new JButton("ȡ��(C)");
		btnCancel.setToolTipText("ȡ���޸ģ����ص�¼����");
		btnCancel.setMnemonic('C');
		
		lblUserName = new JLabel("�û���:");
		lblPassword = new JLabel("ԭ����:");
		lblNewPassword = new JLabel("������:");
		lblConfirmNewPass = new JLabel("ȷ������:");
		
		txtUserName = new JTextField(30);
		pwdPassword = new JPasswordField(30);
		pwdNewPassword = new JPasswordField(30);
		pwdConfirmNewPass = new JPasswordField(30);
		
		/**
		 * �ò��ֲ����ֶ����� 
		 * setBounds�������λ�� 
		 * setFont�������塢���͡��ֺ� 
		 * setForeground�������ֵ���ɫ
		 * setBackground���ñ���ɫ 
		 * setOpaque����������Ϊ͸��
		 */
		pnlChange.setLayout(null); // ������ֶ�����
		pnlChange.setBackground(new Color(52, 130, 203));

		lblUserName.setBounds(50, 80, 100, 30);
		txtUserName.setBounds(150, 80, 120, 25);
		lblPassword.setBounds(50, 115, 100, 30);
		pwdPassword.setBounds(150, 115, 120, 25);
		lblNewPassword.setBounds(50, 150, 80, 30);
		pwdNewPassword.setBounds(150, 150, 120, 25);
		lblConfirmNewPass.setBounds(50, 185, 80, 30);
		pwdConfirmNewPass.setBounds(150, 185, 120, 25);
		
		btnSubmit.setBounds(50, 220, 80, 25);
		btnClear.setBounds(130, 220, 80, 25);
		btnCancel.setBounds(210, 220, 80, 25);
		
		Font fontstr = new Font("����", Font.PLAIN, 12);
		lblUserName.setFont(fontstr);
		lblPassword.setFont(fontstr);
		lblNewPassword.setFont(fontstr);
		lblConfirmNewPass.setFont(fontstr);
		txtUserName.setFont(fontstr);
		pwdPassword.setFont(fontstr);
		pwdNewPassword.setFont(fontstr);
		pwdConfirmNewPass.setFont(fontstr);
		
		lblUserName.setForeground(Color.BLACK);
		lblPassword.setForeground(Color.BLACK);
		lblNewPassword.setForeground(Color.BLACK);
		lblConfirmNewPass.setForeground(Color.BLACK);
		btnSubmit.setBackground(Color.ORANGE);
		btnClear.setBackground(Color.ORANGE);
		btnCancel.setBackground(Color.ORANGE);
		
		pnlChange.add(btnCancel);
		pnlChange.add(btnClear);
		pnlChange.add(btnSubmit);
		pnlChange.add(lblUserName);
		pnlChange.add(lblPassword);
		pnlChange.add(lblNewPassword);
		pnlChange.add(lblConfirmNewPass);
		pnlChange.add(txtUserName);
		pnlChange.add(pwdPassword);
		pnlChange.add(pwdNewPassword);
		pnlChange.add(pwdConfirmNewPass);
		
		// ���ñ���ͼƬ
		Icon logo1 = new ImageIcon("resource/images/loginlogo.jpg");
		lblLogo = new JLabel(logo1);
		lblLogo.setBounds(0, 0, 340, 66);
		pnlChange.add(lblLogo);
		// ���õ�¼����
		setResizable(false);
		setSize(340, 300);
		setVisible(true);
		scrnsize = toolkit.getScreenSize();
		setLocation(scrnsize.width / 2 - this.getWidth() / 2, scrnsize.height
				/ 2 - this.getHeight() / 2);
		Image img = toolkit.getImage("resource/images/appico.jpg");
		setIconImage(img);
		
		// ������ťע�����
		btnSubmit.addActionListener(this);
		btnClear.addActionListener(this);
		btnCancel.addActionListener(this);
	}
	
	/**
	 * ��ť������Ӧ
	 */
	@SuppressWarnings({ "deprecation", "static-access" })
	public void actionPerformed(ActionEvent ae) {
		Object source = ae.getSource();
		if (source.equals(btnSubmit)) {
			// �ж��û����������Ƿ�Ϊ��
			if (txtUserName.getText().equals("") || 
				pwdPassword.getText().equals("") ||
				pwdNewPassword.getText().equals("") ||
				pwdConfirmNewPass.getText().equals("") ) {
				JOptionPane op1 = new JOptionPane();
				op1.showMessageDialog(null, "�û��������벻��Ϊ��");
			} else {
				change();
			}
		} else if (source.equals(btnClear)) {
			txtUserName.setText("");
			pwdPassword.setText("");
			pwdNewPassword.setText("");
			pwdConfirmNewPass.setText("");
		} else if (source.equals(btnCancel)) {
			new Login();
			this.dispose();
		}
	} // actionPerformed()����

	
	/**
	 * �������¼���Ӧ����
	 */
	@SuppressWarnings("deprecation")
	public void change() {
		String newPass = pwdNewPassword.getText();
		String confirmPass = pwdConfirmNewPass.getText();
		if(!newPass.equals(confirmPass)) {
			JOptionPane.showMessageDialog(null, "�����������벻һ�£�����������");
			pwdNewPassword.setText("");
			pwdConfirmNewPass.setText("");
			return;
		}
		// ���ܿͻ�����ϸ����
		Change_Customer data = new Change_Customer(
				txtUserName.getText(),
				pwdPassword.getText(),
				pwdNewPassword.getText());
		try {
			// ���ӵ�������
			Socket toServer;
			toServer = new Socket(strServerIp, 1080);
			ObjectOutputStream streamToServer = new ObjectOutputStream(
					toServer.getOutputStream());
			// д�ͻ���ϸ���ϵ�������socket
			streamToServer.writeObject((Change_Customer) data);
			// �����Է�����socket�ĵ�¼״̬
			BufferedReader fromServer = new BufferedReader(
					new InputStreamReader(toServer.getInputStream()));
			String status = fromServer.readLine();
			if (status.equals(data.custName+"�޸�����ɹ�")) {
				new ChatRoom((String) data.custName, strServerIp);
				this.dispose();
				// �ر�������
				streamToServer.close();
				fromServer.close();
				toServer.close();
			} else {
				JOptionPane.showMessageDialog(null, status);
				// �ر�������
				streamToServer.close();
				fromServer.close();
				toServer.close();
			}
		} catch (ConnectException e1) {
			JOptionPane.showMessageDialog(null, "δ�ܽ�����ָ��������������!");
		} catch (InvalidClassException e2) {
			JOptionPane.showMessageDialog(null, "�����!");
		} catch (NotSerializableException e3) {
			JOptionPane.showMessageDialog(null, "����δ���л�!");
		} catch (IOException e4) {
			JOptionPane.showMessageDialog(null, "����д�뵽ָ��������!");
		}
	}
	
	/**
	 * ������½����
	 * 
	 * @param args
	 */
	public static void main(String args[]) {
		new ChangePass("127.0.0.1");
	}
}
