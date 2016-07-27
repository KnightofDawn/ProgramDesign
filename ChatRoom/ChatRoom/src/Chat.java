/**
 * Title: QICQ����ϵͳ��¼����
 * Description: �������ݶ��� 
 * Copyright: Copyright (c) 2015
 * 
 * @author �����
 * @version 1.0
 */

import java.io.Serializable;
import java.security.PublicKey;

public class Chat implements Serializable {

	private static final long serialVersionUID = 4058485121419391969L;
	public String chatUser; // �������û���
	
	public String chatMessage; // ��������
	
	public String chatToUser; // ���ܶ����û���
	
	public String emote; // �������
	
	public boolean whisper; // �Ƿ�˽��
	
	public Chat() {
		// TODO Auto-generated constructor stub
	}
	
	public Chat(String User, String message,
			String toUser, boolean flag, String emotion) {
		chatUser = User;
		chatMessage = message;
		chatToUser = toUser;
		emote = emotion;
		whisper = flag;
	}
}