<?php

/**
 * �����ɷϥ桼�ƥ���ƥ�
 *
 * @package magicweapon
 * @link http://www.grid-works-guild.net/MagicWeapon/ MagicWeapon
 * @access  public
 * @author  Michiaki Wuzawa <wuzawa@m-fr.net>
 * @create  $LastChangedDate$
 * @version $Revision$
 **/


class code_util {

/**
 * ��ƻ�ܸ�����
 *
 * @access public
 * @param int $i ��ƻ�ܸ�������
 * @return string �����ɤˤ��ä��� ���꤬����ж�ʸ��
 */
static public function prefecture($i)
{
  if (1 > $i) { return ""; }
  if (47 < $i) { return ""; }

  //
  $area_val = array(
    '1' => '�̳�ƻ',
    '2' => '�Ŀ���',
    '3' => '��긩',
    '4' => '�ܾ븩',
    '5' => '���ĸ�',
    '6' => '������',
    '7' => 'ʡ�縩',
    '8' => '��븩',
    '9' => '���ڸ�',
    '10' => '���ϸ�',
    '11' => '��̸�',
    '12' => '���ո�',
    '13' => '�����',
    '14' => '�����',
    '15' => '���㸩',
    '16' => '�ٻ���',
    '17' => '���',
    '18' => 'ʡ�温',
    '19' => '������',
    '20' => 'Ĺ�',
    '21' => '���츩',
    '22' => '�Ų���',
    '23' => '���θ�',
    '24' => '���Ÿ�',
    '25' => '���츩',
    '26' => '������',
    '27' => '�����',
    '28' => 'ʼ�˸�',
    '29' => '���ɸ�',
    '30' => '�²λ���',
    '31' => 'Ļ�踩',
    '32' => '�纬��',
    '33' => '������',
    '34' => '���縩',
    '35' => '������',
    '36' => '���縩',
    '37' => '���',
    '38' => '��ɲ��',
    '39' => '���θ�',
    '40' => 'ʡ����',
    '41' => '���츩',
    '42' => 'Ĺ�긩',
    '43' => '���ܸ�',
    '44' => '��ʬ��',
    '45' => '�ܺ긩',
    '46' => '�����縩',
    '47' => '���츩' );
  //
  return $area_val[$i];
}

/**
 * 62�ʿ��Ѵ�
 *
 * @access public
 * @param int $dec �Ѵ����ο���:10�ʿ�����
 * @return string ���ͤ�62�ʿ����Ѵ�
 */
static public function to62($dec)
{
  //
  $ar = array("0","1","2","3","4","5","6","7","8","9",
              "a", "b","c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m",
              "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z",
              "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M",
              "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"
            );

  //
  $ret = "";

  do {
    $bottom = $dec % 62;
    $ret = $ar[$bottom] . $ret;
    $dec = (int)($dec/62);
  } while($dec);

  return $ret;
}

/**
 * ����ѥե����ޥå�
 *
 * ���头�Ȥ˶�ۤˡ�(���Τˤ�delimiter����)��֤�����
 * XXX ����ͤȤ��ޤ��ƥ��Ȥ��Ƥʤ���
 *
 * @access public
 * @param int $i ���
 * @param string $delimiter �ǥ�ߥ�
 * @return string �ǥ�ߥ��Ƕ��ڤ�줿ʸ����
 */
static public function money_format($i, $delimiter = ',')
{
  $awk = array();
  while(0 !== $i) {
    array_unshift($awk,  sprintf("%03d", $i % 1000));
    $i = (int)floor($i / 1000);
  }

  // XXX ��Ƭ���Ǥ�����padding�������
  $awk[0] = (string)$awk[0] + 0;

  if (false === empty($awk)) {
    $ret = implode($delimiter, $awk);
  } else {
    $ret = '0';
  }

  //
  return $ret;
}

//private:


} // end of class
