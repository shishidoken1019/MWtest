<?php
/**
 * db�ˤޤĤ��桼�ƥ���ƥ�
 *
 * ������֥͡���ץ��SQL�Ǥ��ä���ǡ������ۤ����׻���
 *
 * @package magicweapon
 * @link http://www.grid-works-guild.net/MagicWeapon/ MagicWeapon
 * @access  public
 * @author  Michiaki Wuzawa <wuzawa@m-fr.net>
 * @create  $LastChangedDate$
 * @version $Revision$
 **/

class db_util {

/**
 * �ǡ����켰����
 *
 * SQL�ǻ��ꤵ�줿�ǡ�����켰����
 * �ǡ��������������ˤʤ�
 *
 * @access public
 * @param db_handle $dbh db_handle���饹(������������饹)�Υ��󥹥���
 * @param string $sql SQLʸ
 * @return array ���Τˤϡ�array(array))�ס����󤬤ʤ���������
 */
static public function get_row_data_array($dbh, $sql)
{
  $ret = array();
  $res = $dbh->query($sql);
  if (empty($res)) {
    return $ret;
  }
  while($res->fetch()) {
    $ret[] = $res->get_row();
  }
  //
  return $ret;
}

/**
 * �ǡ������
 *
 * SQL�ǻ��ꤵ�줿�ǡ�������ʬ����
 * �ǡ���������ˤʤ�
 *
 * @access public
 * @param db_handle $dbh db_handle���饹(������������饹)�Υ��󥹥���
 * @param string $sql SQLʸ
 * @return array 1��ʬ������ǡ����󤬤ʤ���������
 */
static public function get_row_data($dbh, $sql)
{
  $ret = array();
  $res = $dbh->query($sql);
  if (empty($res)) {
    return $ret;
  }
  if($res->fetch()) {
    $ret = $res->get_row();
  }
  //
  return $ret;
}

/**
 * �ǡ�������
 *
 * SQL�ǻ��ꤵ�줿�ǡ��������
 *
 * @access public
 * @param db_handle $dbh db_handle���饹(������������饹)�Υ��󥹥���
 * @param string $sql SQLʸ
 * @return string ���������ǡ������ʤ����϶�ʸ����
 */
static public function get_mono_data($dbh, $sql)
{
  $ret = "";
  $res = $dbh->query($sql);
  if (empty($res)) {
    return $ret;
  }
  if($res->fetch()) {
    $ret = $res->get_data(0);
  }
  //
  return $ret;
}


} // end of class
