<?php

/**
 * ��Ū�ʻ񸻤���Ϥ��뤿��Τ��������饹
 *
 * MW��MVC�Ȥä�������Ū��HTML�Ȥ��Ф��ѤΥ��饹��
 * �����Ȥ�css�Ȥ��ϤȤꤢ����̤����
 * �񸻤ϥ�������ʥǥ������ˤ��뤳�Ȥ�����
 * config�ե������ base_dir ����ǥ��쥯�ȥ�Ȥߤʤ�
 *
 * @package magicweapon
 * @link http://www.grid-works-guild.net/MagicWeapon/ MagicWeapon
 * @access  public
 * @author  Michiaki Wuzawa <wuzawa@m-fr.net>
 * @create  $LastChangedDate$
 * @version $Revision$
 **/

require_once('config.inc');

class static_resource_localdisk {

public function __construct()
{
  //
  $this->init();
}

//
public function init()
{
  $this->set_config_obj(null);
}

//
protected function set_config_obj($o) { $this->config_ = $o; }
protected function get_config_obj() { return $this->config_; }

/**
 * config�ե�����̾�Υ��å�
 *
 * ��Ǥ⤷��������set_config�Υ�åѡ������뤫��
 *
 * @access public
 * @param string $fn config�ե�����̾
 * @return boolean �������꤬�����false
 */
public function set_config_file($fn)
{
  $obj = new config;
  $obj->set_file($fn);
  $this->set_config_obj($obj);
  //
  return true;
}

/**
 * ����ƥ�ĤΥե�����̾����
 *
 *
 * @access public
 * @param string $id ���̻�
 * @return string �������꤬���ä����ʸ��
 */
public function get_contents_filename($id)
{
  $ret = $this->get_config_obj()->find($id);
  return $ret;
}

//private:
private $config_;

} // end of class
