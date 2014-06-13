<?php
/**
 * ����ե����졼�����ե����� ���ϥ��饹
 *
 * ������ name = value �����פ�config�������
 *
 * @package magicweapon
 * @link http://www.grid-works-guild.net/MagicWeapon/ MagicWeapon
 * @access  public
 * @author  Michiaki Wuzawa <wuzawa@m-fr.net>
 * @create  $LastChangedDate$
 * @version $Revision$
 */

class config {

//
public function __construct()
{
  $this->init();
}

//
public function init()
{
  // ����ˤ���
  $this->list_ = array();
}

/**
 * config�ե�����̾����
 *
 * �ºݤˤ�parce���äƤ�
 * ��긷̩�ˤϡ�parce���Ƥ�Τ�set�᥽�åɤ�����
 *
 * @access public
 * @param string $filename config�ե�����̾
 * @return boolean �������꤬�����false
 */
public function set_file($filename)
{
  if ("" == $filename) {
    return false;
  }

  if(!($fp = @fopen($filename, "r"))) {
    return false;
  }

  $ret = array();
  // XXX
  while($wk=fgets($fp, 10240)) {
    $wk = rtrim($wk); // ���ԥ����ɤκ��
    array_push($ret, $wk);
  }

  //
  return $this->set($ret);
}

/**
 * config�ǡ�������
 *
 * �ºݤˤ�parce���äƤ�
 *
 * @access public
 * @param array $datas string�ʥǡ���������
 * @return boolean �������꤬�����false
 */
public function set(array $datas)
{
  foreach ($datas as $wk) {
    // ��Ƭ�Υۥ磻�ȥ��ڡ����ν���
    $wk = ltrim($wk);

    // �����Ԥ�̵��
    if ("" === $wk) {
      continue;
    }
    // �����ȥ����Ȥν���
    if ('#' === $wk[0]) {
      continue;
    }
    // ��ʸ���ܤ�=(name�ʤ�)��̵��
    if ('=' === $wk[0]) {
      continue;
    }
    // ʸ�����=����Ĥ�ʤ����̵��
    if (false === strpos($wk, '=')) {
      continue;
    }

    // ����
    // XXX
    array_push($this->list_, $wk);
//print "set $wk\n";
  }
//var_dump($this->list_);

  return true;
}

////////////////////////////////////////////////
// �ʲ���������

/**
 * ñ����ܤθ���
 *
 * �ºݤˤϥ�åѡ�
 *
 * @access public
 * @param string $name ��������
 * @return string �������줿�͡��ʤ����϶�ʸ��
 */
public function find($name)
{
  if ($ret = $this->find_array($name)) {
    return $ret[0];
  }

  return "";
}

/**
 * ����
 *
 * @access public
 * @param string $name ��������
 * @return array �������줿�͡��ʤ����϶�����
 */
public function find_array($name)
{
//
$ret = array();
//var_dump($name);

  // �֤�󤷤Ƹ���
  foreach ($this->list_ as $wk) {
    if ( 1 == (preg_match( '/^[ \t]*' . $name . '[ \t]*[=][ \t]*(.*)/' , $wk, $buf)) ) {
      // �����Ԥν���
      $w = $buf[1];
      $w = trim($w);
      // XXX quoted_string����򤳤��Ǥ��ͽ�ꡧ̤����
      array_push($ret , $w);
    }
  }

  return $ret;
}

/**
 * is�ϸ���
 *
 * ���ꤵ�줿name���б�����value����true�Ȥ�yes�Ȥ�on�Ȥ�������ʴ����ʤ�true���֤�
 *
 * @access public
 * @param string $name ��������
 * @return boolean �ʤ󤫹���Ū���ͤ��ä���true
 */
public function is($name)
{
  $s = $this->find($name);
  $awk = array('true', 'ok', 'yes', '1', 'y');
  $ret = false;
  foreach($awk as $wk) {
    if (0 === strcasecmp($s, $wk)) {
      $ret = true;
      break;
    }
  }

  //
  return $ret;
}


//private:
private $list_;

} // end of class
