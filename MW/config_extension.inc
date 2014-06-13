<?php

/**
 * config��ĥ���饹
 *
 * ��ǽ���ĥ��������ե������饹
 * - @include�ˤ����̥ե�����μ����ߡפ򥵥ݡ���
 *   ����:
 *     @include('/opt/www/products/conf/extension.conf')
 *     @include_wbp('conf/extension.conf')
 *
 * - base_path�����̾����'_wbp'ź�äˤ�롢���ǥ��쥯�ȥ�Υ��ݡ���
 *
 * @package magicweapon
 * @link http://www.grid-works-guild.net/MagicWeapon/ MagicWeapon
 * @access  public
 * @author  Michiaki Wuzawa <wuzawa@m-fr.net>
 * @create  $LastChangedDate$
 * @version $Revision$
 **/

require_once('config.inc');

class config_extension extends config {

public function __construct()
{
  //
  parent::__construct();
  //$this->init();
}

//
public function init()
{
  parent::init();
  $this->set_base_path('');
}

//
protected function set_base_path($s) { $this->base_path_ = $s; }
protected function get_base_path() { return $this->base_path_; }



/**
 * config�ǡ�������
 *
 * @access public
 * @param array $datas string�ʥǡ���������
 * @return boolean �������꤬�����false
 */
public function set(array $datas)
{
//print "Trap 1\n";
  // �ޤ��ƽ�������
  $ret = parent::set($datas);

  /////////////////
  // �ǡ���ĥ����
  /////////////////
  // base_path�μ���
  $s = parent::find('base_path');
  if ("" !== $s) {
    $this->set_base_path($s);
//var_dump($s);
  }

  // @include�ν���
  foreach ($datas as $wk) {
    // ��Ƭ�Υۥ磻�ȥ��ڡ����ν���
    $wk = ltrim($wk);

    // XXX �Ȥꤢ�����٥��˺���
    if ( 0 === strncmp('@include', $wk, 8)) {
      $awk = explode('\'', $wk);
      $path = $awk[1];
      if (("" !== $this->get_base_path())&&(0 === strncmp('@include_wbp', $wk, 12))) {
        $path = $this->get_base_path() . $path;
      }
//var_dump($path);
      //
      $this->set_file($path);
    }
  }

  //
  return true;
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
$ret2 = array();

  // �ޤ��̾省���θ���
  $ret = parent::find_array($name);

  // base_path���꤬�������ĥ����
  $bp = $this->get_base_path();
//var_dump($bp);
  if ("" !== $bp) {
    $ret2 = parent::find_array($name . '_wbp');
    foreach($ret2 as $wk) {
      $ret[] = $bp . $wk;
    }
  }

  //
  return $ret;
}


//private:
private $base_path_;

} // end of class
