<?php

/**
 * MW用 Smartyラッパー
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
 * 単置換のラッパー
 *
 * @access public
 * @param string $n 名前
 * @param string $v 名前
 * @return 戻り値の型 簡単な説明
 */
public function monoDic($n, $v)
{
  $this->assign($n, $v);
}

/**
 * 複置換のラッパー
 *
 * XXX 相当にアバウト orz
 *
 * @access publicかprivateかprotectedか
 * @param 型 名前 説明
 * @return 戻り値の型 簡単な説明
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

