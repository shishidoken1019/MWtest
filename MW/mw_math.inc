<?php

/**
 * MW�ο��إ��饹
 *
 * @package magicweapon
 * @link http://www.grid-works-guild.net/MagicWeapon/ MagicWeapon
 * @access  public
 * @author  Michiaki Wuzawa <wuzawa@m-fr.net>
 * @create  $LastChangedDate$
 * @version $Revision$
 **/

class mw_math {

/**
 * ʿ���������
 *
 * ������GMP(Ǥ��Ĺ����)�Ǥ�OK�ʤ����꤬�ݥ����
 *
 * @access public
 * @param int�ޤ���GMP���֥������� $x ʿ�������᤿����
 * @return float(�äĤ�double) ʿ����
 */
static public function sqrt($x)
{
  list($a, $b) = gmp_sqrtrem($x);
  $a = gmp_strval($a);
  $b = gmp_strval($b);
  $c = sqrt(pow($a, 2) + $b) - $a;
  $pp = $a + $c;

  //
  return $pp;
}


/**
 * ʿ���ͤ����
 *
 * ���ʤ겾��Ū�ʥ᥽�åɡ�����Ū�ˤ�vector�ޤ��� vector<vector>��������
 * ñ������󤬰���ѥ�᥿�ʤ顢������Ф���������
 * �����������פ�����ѥ�᥿�ʤ顢return ��ޤ������������פˤʤ롣
 * type�Ǹ����������Τϰʲ����̤�
 *   'arithmetical' : ���ʿ��(�ǥե����)
 *
 * @access public
 * @param array(vector)�ޤ���array(vector<vector>) $base ��
 * @param string $type ʿ���ͤμ���
 * @return array(hash)�ޤ���array(vector<hash>) ����͡�value:ʿ����, total:�����: count:�ǡ����Ŀ�
 */
static function average(array $base, $type = 'arithmetical')
{

}



} // end of class
