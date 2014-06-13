<?php

/**
 * ���å����ǡ����ݻ����饹
 *
 * ���å���������ݻ����륯�饹
 * �ºݤˤ�Virtual�ʥ��饹�ʤΤǷѾ��褸��ʤ��ȥ��󥹥��󥹺��ʤ���
 *
 * @package magicweapon
 * @link http://www.grid-works-guild.net/MagicWeapon/ MagicWeapon
 * @access  public
 * @author  Michiaki Wuzawa <wuzawa@m-fr.net>
 * @create  $LastChangedDate$
 * @version $Revision$
 */

require_once("cgi_param.inc");

// XXX �ǡ�������Ū�ˤ��줬�����ʤΤ�cgi_param����Ѿ���
abstract class session_data extends cgi_param {
//public:

public function __construct()
{
  $this->valid_time_ = 15 * 60;
  parent::__construct();
}

/**
 * ���å����ID������
 *
 * @access public
 * @param string $id ���å����ID
 */
public function set_id($id) { $this->id_ = $id; }
/**
 * ���å����ID�μ���
 *
 * @access public
 * @return string ���å����ID
 */
public function get_id() { return $this->id_; }

/**
 * ͭ������(TTL)������
 *
 * 0�ޤ�������ͤ���ꤹ���̵���¤Ȥߤʤ�
 * default��15ʬ�Ǥ���
 *
 * @access public
 * @param int $t TTL���ͤ��ä�
 */
public function set_validity_term($t) { $this->valid_time_ = $t; }

/**
 * ͭ������(TTL)�μ���
 *
 * 0�ޤ�������ͤ���ꤹ���̵���¤Ȥߤʤ�
 *
 * @access public
 * @return int TTL���ͤ��ä�
 */
public function get_validity_term() { return $this->valid_time_; }

/**
 * �񤭹���(Virtual)
 *
 * @access public
 * @return boolean ���꤬�����false
 */
abstract public function write();

/**
 * �ɤ߹���(Virtual)
 *
 * @access public
 * @return boolean ���꤬�����false
 */
abstract public function read();

/**
 * ���(Virtual)
 *
 * @access public
 * @return boolean ���꤬�����false
 */
abstract public function del();

/**
 * ���å����ID��¸�߳�ǧ(Virtual)
 *
 * �񤭹�����ˤ��Ǥ˥��å����ID��¸�ߤ��Ƥ��뤫�γ�ǧ
 * ����Ū�ˡ�true�����äƤ������񤭤ˤʤꤽ���ʤΤ�Ŭ���н�פΥ��᡼��
 *
 * @access public
 * @return boolean ���Ǥ�¸�ߤ��Ƥ����true
 */
abstract public function is_session();

//private:
private $id_;
private $valid_time_; // ͭ�����֡�ñ�̤���
} // end of class
