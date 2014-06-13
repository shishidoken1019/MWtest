<?php

/**
 * debug��util���饹
 *
 * @package magicweapon
 * @link http://www.grid-works-guild.net/MagicWeapon/ MagicWeapon
 * @access  public
 * @author  Michiaki Wuzawa <wuzawa@m-fr.net>
 * @create  $LastChangedDate$
 * @version $Revision$
 **/

class debug_util {

/**
 * ʸ�����char�����ɽ���
 *
 * @access public
 * @param string& $s ���Ϥ�����ʸ����ؤλ���
 * @param boolean $flg ������true�ʤ鸵ʸ�������ϡ�false�ʤ�̤����
 * @return string ������ʸ����
 */
static public function dump_string(&$s, $flg = true)
{
//var_dump($s);
  $len = strlen($s);
  if (true === $flg) {
    $ret = $s . '(';
  } else {
    $ret = '(';
  }
  for($i = 0; $i < $len; $i ++) {
    $ret .= sprintf("(%02x)", ord($s[$i]));
  }
  $ret .= ')';
  return $ret;
}
/**
 * ʸ�����char�����ɽ���:stdout��äѡ�
 *
 * @access public
 * @param string& $s ���Ϥ�����ʸ����ؤλ���
 * @param boolean $flg ������true�ʤ鸵ʸ�������ϡ�false�ʤ�̤����
 */
static public function dump_string_put(&$s, $flg = true)
{
  print debug_util::dump_string($s, $flg) . "\n";
}

/**
 * debug_backtrace�ؿ���������
 *
 * @access public
 * @return string ������ʸ����
 */
static public function backtrace_string()
{
  //
  $awk = debug_backtrace();

  // ����ܤϼ�ʬ��call���Ƥ�Τ��狼�äƤ뤫����
  array_shift($awk);

  // ���Ѥߤ��Ƥ�äݤ��Τ������ȿž
  // XXX ��С������ƥ졼�ȤȤ�����㤤���Τ� orz
  $awk = array_reverse($awk);

  $ret_array = array();
  foreach($awk as $wk) {
//var_dump($wk['class']);
//var_dump($wk['function']);
//var_dump($wk['args']);
    //
    $ret = $wk['class'] . $wk['type'] . $wk['function'] . '(';

    // XXX empty������Τ䤱�ɤʤ�
    if (false === empty($wk['args'])) {
      $type_awk = array();
      foreach($wk['args'] as $wk_args) {
        $type_awk[] = gettype($wk_args) . ' ' . $wk_args;
      }
      $ret .= implode(', ', $type_awk);
    }

    //
    $ret .= ')';

    //
    $ret_array[] = $ret;
  }
  //
  $ret = implode(' => ', $ret_array);

  //
  return $ret;
}



//private:


} // end of class
