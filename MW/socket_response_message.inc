<?php

/**
 * �����åȤ˴ؤ��������å������򰷤����饹
 *
 * �꥿���󥳡��ɤȥ�å�����
 *
 * @package magicweapon
 * @access  public
 * @author  Yuuki Ogura <hiruandon2nd@gmail.com>
 * @create  2006/10/13
 * @version $Id$
 **/
class socket_response_message {

	/*
	 * ���󥹥ȥ饯��
	 */
	public function __construct() { $this->init(); }

	/*
	 * �����
	 */
	public function init() {}

	/*
	 * �����åȤ���α�����å������򥻥åȤ��ơ�
	 * ���������ɤȥ�å�������ʬ��ʬ�䡣
	 */
	public function set_string($s) {
		$this->response_str_ = $s;
		$this->split_string();
	}
	public function get_string()   { return $this->response_str_; }

	/*
	 * ������å������򡢱��������ɤȥ�å�������ʬ��ʬ�䤷�ƥ��å�
	 * XXX ���������ɤΥ��å�����get_code()
	 * XXX ������å������Υ��å�����get_message()
	 */
	private function split_string() {
		$this->code_    = substr($this->get_string(), 0,3);
		$this->message_ = substr($this->get_string(), 3);
	}
	public function get_code()    { return $this->code_; }
	public function get_message() { return $this->message_; }

	/*
	 * ������å����������顼�ʤΤ�Ƚ��
	 */
	public function is_error() {

		$wk = $this->get_code();
		$wk = $wk . "";
		// ��Ƭ�ο�����������
		switch ($wk[0]) {
			case 2:
			case 3:
				$bol = false;
				break;
			case 4:
			case 5:
				$bol = true;
				break;
			default:
				$bol = true;
		}

//print "get_code:" . $this->get_code() . "\n";
//print "get_message:" . $this->get_message() . "\n";

		return $bol;
		
	}

	private $response_str_;	// �����åȤ���α�����å�����
	private $code_;					// ����������
	private $message_;				// ������å�����

}
