<?php

/**
 * MW�� Smarty��åѡ�
 *
 * @package magicweapon
 * @link http://www.grid-works-guild.net/MagicWeapon/ MagicWeapon
 * @access  public
 * @author  Michiaki Wuzawa <wuzawa@m-fr.net>
 * @create  $LastChangedDate$
 * @version $Revision$
 **/

require_once('Smarty.class.php');

class mw_smarty extends Smarty {

/**
 * ñ�ִ��Υ�åѡ�
 *
 * @access public
 * @param string $n ̾��
 * @param string $v ̾��
 * @return ����ͤη� ��ñ������
 */
public function monoDic($n, $v)
{
  $this->assign($n, $v);
}

/**
 * ʣ�ִ��Υ�åѡ�
 *
 * XXX �����˥��Х��� orz
 *
 * @access public��private��protected��
 * @param �� ̾�� ����
 * @return ����ͤη� ��ñ������
 */
public function multiDic($n, $v)
{
  $cn = get_class($v);
//var_dump($cn);

   if ('simple_put' === $cn) {
     $this->assign($n, 1);
   }
}


//private:


} // end of class
