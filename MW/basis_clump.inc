<?php

/**
 * clump�ϺǴ��쥯�饹
 *
 * ����ե�����ʤɤ�ưŪ���Ѳ�����ֹ�¤�Υ��饹��
 * XXX struct clump�Ȥ�����̾���Ǥ�褫�ä��Τ��ʤ���
 * multimap�ϤȤꤢ�������ꤷ�Ƥ��ʤ��Τǡ�data��PHPŪ�ˤϥϥå���Ǥ褤���ʤ���
 *
 * @package magicweapon
 * @link http://www.grid-works-guild.net/MagicWeapon/ MagicWeapon
 * @access  public
 * @author  Michiaki Wuzawa <wuzawa@m-fr.net>
 * @create  $LastChangedDate$
 * @version $Revision$
 **/

class basis_clump {

public function __construct()
{
  //
  $this->init();
}

//
public function init()
{
  // ���Ǥ�켰clear
  $this->init_data();
  $this->allname_ = array();
}

/**
 * �ͤΤߤ������ꥢ����
 *
 * @access public
 */
public function init_data()
{
  // ���Ǥ�켰clear
  $this->data_ = array();
}

//
public function get_all_names() { return $this->allname_; }


/**
 * setter
 *
 * �ͤ����ꤹ�롣���Ǥ�¸�ߤ���name����ꤷ�����Ͼ��
 *
 * @access public
 * @param string $n ���ꤹ��ǡ�����̾��
 * @param string $v ���ꤹ��ǡ�������
 */
public function set_data($n, $v) { $this->data_[$n] = $v; }

/**
 * getter
 *
 * �ͤ�������롣���ꤵ��Ƥ��ʤ��ͤξ��϶�ʸ�����֤롣
 * ¸�ߥ����å���is_name�򤷤褦���뤳�ȡ�
 *
 * @access public
 * @param string $n �����������ǡ�����̾��
 * @return string �����ǻ��ꤷ��name���б������͡�¸�ߤ��ʤ����϶�ʸ��
 */
public function get_data($n)
{
  if (false === $this->is_name($n)) {
    return "";
  }
  if (false === isset($this->data_[$n]) ) {
    return "";
  }
  return $this->data_[$n];
}

/**
 * ¸�ߥ����å�
 *
 * name�ǻ��ꤵ�줿�ͤ�¸�ߤ��Ƥ��뤫�ɤ��������å�
 * �ºݤˤϡ�����ե�����ǻ��ꤵ��Ƥ������ɤ����פΥ����å���
 *
 * @access public
 * @param string $n �ǡ�����̾��
 * @return boolean ¸�ߤ��Ƥ���true��¸�ߤ��Ƥ��ʤ����false
 */
public function is_name($n)
{
  if(empty($this->allname_)) {
    return false;
  }
 return in_array($n, $this->allname_);
}

/**
 * �ǡ���������
 *
 * ���Ǥ��İ���Ѥ߾夲��褦��add���Ƥ���
 * XXX ���Υ����ߥ󥰤ˤ�����data����Ȥ�����Ȥ���
 *
 * @access public
 * @param string $n ���Ǥ�̾��
 * @return boolean ���Ǥ�¸�ߤ��Ƥ���false
 */
public function push_element($n)
{
  if (true === $this->is_name($n)) {
    return false;
  }
  $this->allname_[] = $n;
  return true;
}

//private:
private $data_;		// �ǡ����켰
private $allname_;	// ����̾�켰����

} // end of class
