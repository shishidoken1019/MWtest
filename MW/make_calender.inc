<?php
/**
 * ���������������饹
 *
 * ������������Ϥ���
 *
 * @package magicweapon
 * @access  public
 * @author  Michiaki Wuzawa <wuzawa@m-fr.net>
 * @create  yyyy/mm/dd
 * @version $Id$
 **/

/*
 ���Ͱʲ��Τ褦�ʥƥ�ץ졼�Ȥǽ��Ϥ�Ԥ�

  <tr id="day">
    <td id="txtred">��</td>
    <td>��</td>
    <td>��</td>
    <td>��</td>
    <td>��</td>
    <td>��</td>
    <td>��</td>
    <td id="empty">&nbsp;</td>
  </tr>
$$$loop$$$
    <tr>
        <td>%%%d0%%%
        <td>%%%d1%%%
        <td>%%%d2%%%
        <td>%%%d3%%%
        <td>%%%d4%%%
        <td>%%%d5%%%
        <td>%%%d6%%%
    </tr>
$$$/loop$$$

  �⤷�ܥ���ˤ�������硢

$$$loop$$$
        <td><input type="submit" name="btnDay" value="%%%d0%%%" %%%opt0%%%>
        <td><input type="submit" name="btnDay" value="%%%d1%%%" %%%opt1%%%>
        <td><input type="submit" name="btnDay" value="%%%d2%%%" %%%opt2%%%>
        <td><input type="submit" name="btnDay" value="%%%d3%%%" %%%opt3%%%>
        <td><input type="submit" name="btnDay" value="%%%d4%%%" %%%opt4%%%>
        <td><input type="submit" name="btnDay" value="%%%d5%%%" %%%opt5%%%>
        <td><input type="submit" name="btnDay" value="%%%d6%%%" %%%opt6%%%>
$$$/loop$$$
�Ȥ��뤳�Ȥǡ����դΤʤ��ܥ���ϲ����ʤ��ʤ��

*/

require_once('calender.inc');
require_once('conv.inc');

class make_calendar {

function set_year($s) { $this->yy_ = $s; }
function set_month($s) { $this->mm_ = $s; }

function get_year() { return $this->yy_;  }
function get_month() { return $this->mm_; }

function m_conv($s_base,$p) {

  // �ǡ����ꥹ��
  $list = array();

  $cal_obj = new calender;

  $cal_obj->set_year($this->get_year());
  $cal_obj->set_month($this->get_month());

  // �����μ���
  $cal_obj->set_matubi();

  $misoka = $cal_obj->get_day();

  // ����ǯ��Σ����������μ���
  $cal_obj->set_day(1);

  //  ����ͤϣ������ޤǡ���->�������ȤϤƤ��ȡ��ˡ�
  $fw = $cal_obj->get_week();
//print $obj->get_year() . $obj->get_month() . "\n";
//print "fw is $fw \n";

  // �ᥤ�����
  $dd = 1;         // ����
  $label = 0;       // �������ѥ�٥롣̵����äѤ飰��������
  $swk = "";         // �����ʸ����

  // �������鳢���ޤǤ֤��
  while($misoka >= $dd) {
    // �콵��ñ�̤ǽ���������ǥ롼�פ���ȴ�����ǽ��������Τ�����!!
    for( $j = 0; $j < 7; $j++ ) {
      if ($fw > 0) {
        // ��콵�Ρֽ��Ϥ��ʤ���ʬ�פλ���
        $swk .= '0,';
        $fw --;
      } else {
        // �̾�Ρ����դ�push��
        $swk .= $dd . ',';
        $dd ++;
        if ($misoka < $dd) {
          break;
        }
      }
    }

    // ������������γ�Ǽ
    $list[$label] = $swk;
    $swk = "";
    $label ++;
  }

  // �����
  if ("" != $swk) {
    $list[$label] = $swk;
  }

  // ����ʸ�����ִ�
  foreach($list as $wk) {

    $c = new f_conv;

    $dd = split("\,", $wk);

    for($i = 0; $i < 7; $i++) {
          if(!isset($dd[$i])) {
        $dd[$i] = 0;
      }

      // XXX �Ȥꤢ�������ʤ��̤���ϡפ����ɡ���ǻ���Ǥ���褦�ˤ��롩

      if (0 == $dd[$i]) {
        $c->monoDic(('d' . $i), "");
        $c->monoDic("opt". $i,"disabled");
      } else {
        $c->monoDic(('d' . $i), $dd[$i]);
        $c->monoDic("opt". $i,"");
      }
    }
    $ret .= $c->conv($s_base);
  }

  //
  return $ret;
}

//private:
private $yy_;    // ǯ
private $mm_;    // ��

} // end of class

