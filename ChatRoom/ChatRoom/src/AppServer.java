import java.io.*;
import java.net.*;
import java.util.*;

/**
 * Title: QICQ����ϵͳ����������
 * Description: ��������� 
 * Copyright: Copyright (c) 2015
 * �������ӣ�http://blog.csdn.net/u013007900
 * 
 * ����������
 * 
 * @author �����
 * @version 1.0
 * 
 */
public class AppServer extends Thread {
	private ServerSocket serverSocket;

	private ServerFrame sFrame;

	private static Vector userOnline = new Vector(1, 1);

	private static Vector v = new Vector(1, 1);

	/**
	 * ���������� �����������1080�˿�
	 * ���������sock5�Ĵ�����ַ
	 */
	public AppServer() {
		sFrame = new ServerFrame();
		try {
			serverSocket = new ServerSocket(1080);
			// ��ȡ����������������IP��ַ
			InetAddress address = InetAddress.getLocalHost();
			sFrame.txtServerName.setText(address.getHostName());
			sFrame.txtIP.setText(address.getHostAddress());
			
			sFrame.txtPort.setText("1080");
		} catch (IOException e) {
			fail(e, "������������");
		}
		sFrame.txtStatus.setText("������...");
		this.start(); // �����߳�
	}

	/**
	 * �˳�������
	 * 
	 * @param e
	 *            �쳣
	 * @param str
	 *            �˳���Ϣ
	 */
	public static void fail(Exception e, String str) {
		System.out.println(str + " ��" + e);
	}

	/**
	 * �����ͻ������󣬵����û�����ʱ���� Connection�߳�
	 */
	public void run() {
		try {
			while (true) {
				// ���������ܿͻ�������
				Socket client = serverSocket.accept();
				// ֧�ֶ��߳�
				new Connection(sFrame, client, userOnline, v);
				// System.out.println("userLength:"+userLength);
			}
		} catch (IOException e) {
			fail(e, "���ܼ�����");
		}
	}

	/**
	 * ����������
	 */
	public static void main(String args[]) {
		new AppServer();
	}
}