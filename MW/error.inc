<?php
/**
 * error
 *
 * ���顼���饹
 * 
 * ���顼�δ��쥯�饹
 * 
 *
 * @package magicweapon
 * @author  Yuuki Ogura <hiruandon2nd@gmail.com>
 * @create   2007/06/26
 * @updater  Yuuki Ogura <hiruandon2nd@gmail.com>
 * @update   2007/06/26
 * @version 1.0
 */
class error
{
	/**
	 * ���󥹥ȥ饯��
	 * 
	 * @access public
	 * @param  void
	 * @return void
	 */
	public function __construct() {
		$this->init();
	}

	/**
	 * �����
	 * 
	 * @access public
	 * @param  void
	 * @return void
	 */
	public function init() {
		
	}


	/**
	 * ���顼�����ɤ����ꤹ��
	 *
	 * @access public
	 * @param  integer $i ���顼������
	 * @return void
	 */
	public function set_error_code($i) {
		$this->error_code_ = $i;
	}

	/**
	 * ���顼���ȥ�󥰤����ꤹ��
	 *
	 * @access public
	 * @param  string $s ���顼���ȥ��
	 * @return void
	 */
	public function set_error_string($s) {
		$this->error_string_ = $s;
	}


	/**
	 * ���顼�����ɤ��֤�
	 *
	 * @access public
	 * @param  void
	 * @return integer ���顼������
	 */
	public function get_error_code() {
		return $this->error_code_;
	}

	/**
	 * ���顼���ȥ�󥰤��֤�
	 * 
	 * XXX ���顼�����ɤ���ʸ������֤��ۤ��������Ȼפ�
	 *
	 * @access public
	 * @param  void
	 * @return string ���顼���ȥ��
	 */
	public function get_error_string() {
		return $this->error_string_;
	}




	/**
	 * ���顼�����ɳ�Ǽ
	 * 
	 * @access private
	 * @var    integer
	 */
	private $error_code_;

	/**
	 * ���顼���ȥ�󥰳�Ǽ
	 * 
	 * @access private
	 * @var    string
	 */
	private $error_string_;


}	// end of class

