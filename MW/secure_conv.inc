<?php

/**
 * �����奢��CONV���饹
 *
 * @package magicweapon
 * @link http://www.grid-works-guild.net/MagicWeapon/ MagicWeapon
 * @access  public
 * @author  Michiaki Wuzawa <wuzawa@m-fr.net>
 * @create  $LastChangedDate$
 * @version $Revision$
 **/

require_once('conv.inc');
require_once('security.inc');

class secure_conv extends f_conv {

public function __construct()
{
  // XXX �ƥ��饹��init���ʤ�����Ȥꤢ�����ä��Ȥ�
  parent::__construct();
  //$this->init();
}

//
public function init()
{
  parent::init();
}

/**
 * �����奢��ñ�ִ���Ͽ
 *
 * @access public
 * @param string $name ̾��
 * @param string $value ��
 * @return boolean �������꤬�����false
 */
public function monoDic($name, $value) 
{
  //
  return parent::monoDic($name, security::sanitize_html($value));
}

/**
 * ���˥������������ʤ��Ȥ��Ѥ�ñ�ִ�����
 *
 * @access public
 * @param string $name ̾��
 * @param string $value ��
 * @return boolean �������꤬�����false
 */
public function monoDic_unsecure_raw($name, $value)
{
  //
  return parent::monoDic($name, $value);
}



//private:


} // end of class
