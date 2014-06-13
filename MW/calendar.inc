<?php

/**
 * �����������饹
 *
 * ���դˤޤĤ�����̤򰷤�
 *
 * @package magicweapon
 * @access  public
 * @author  Michiaki Wuzawa <wuzawa@m-fr.net>
 * @create  yyyy/mm/dd
 * @version $Id$
 **/


/*
 * ���å���
 *
 * get_year();
 * get_month();
 * get_day();
 * get_hour();
 * get_minute();
 * get_second();
 * get_min();  // get_minute��Ʊ��
 * get_sec();  // get_second��Ʊ��
 * get_epoc(); // ���ݥå�������
 * get_week(); // 0:����6:��
 * get_week_string(); // �����αѸ�̾
 * get_week_string_short();  // �����Σ�ʸ���Ѹ�̾
 * get_month_string();  // ��αѸ�̾
 * get_month_string_short(); // ��Σ�ʸ���Ѹ�̾
 * get_julian(); // ��ꥦ����
 *
 * // 'yyyy/mm/dd hh:mm:ss' ������ʸ����
 * // $separator�� "/" ��ʬ��ʸ������
 * get_string($separator); 
 * get_stringZ($separator);  // "GMT", "+900"�ղ�
 *
 * get_string_for_cookie();  // ���å��������λ���ʸ����
 * get_weeks_number_of_month(); // ���դ����η���貿����
 *
 **********************
 * ���å���
 *
 * set_year($num);
 * set_month($num);
 * set_day($num);
 * set_hour($num);
 * set_minute($num);
 * set_second($num);
 * set_min($num);
 * set_sec($num);
 * set_epoc($epoc);  // ���ݥå������फ�饻�å�
 * set_julian($jd);  // ��ꥦ�������饻�å�
 * set_string($str); // ʸ���󤫤饻�å�
 * set_stringApache($str); // apache���������դ��饻�å�
 * set_matubi(); // ���η�����������դ򥻥å�
 * set_zone($str); // �����ӥ����󥻥åȡʥǥե���Ȥ� "+0900"��
 * set_zoneJST();  // ������� "+0900"�˥��å�
 * set_zoneGMT();  // ������� "GMT"�˥��å�
 * set_zoneJ();  // set_zoneJST��Ʊ��
 *
 * set_now_date();  // ���դ򸽺߻���˥��å�
 * set_birth_day_from($age); // $age�ФǤ�������Τ��������򥻥å�
 * set_birth_day_to($age);  // $age�ФǤ�����ֺǶ���������򥻥å�
 *
 **********************
 *
 * is();  // ���դ�������������å�
 * calculation_day($num);  // $num�������ˤ������դ򤺤餹
 * calculation_hour($num); // $num�ʻ��֡ˤ������֤򤺤餹
 *
 * // $cal(�����������֥�������)��������ӡ�Ʊ���ʤ�true
 * equal($cal); // ���Ƥ����Ǥ����
 * equal_date($cal); // ���դ����
 * equal_time($cal); // ���֤����
 *
*/

/**
 * calendar
 *
 * �����������饹
 *
 * @author
 * @package
 * @since
 */
class calendar
{

/**
 * __construct
 *
 *
 * @param ������������
 * @return  ����ͤ�����
 * @access public
 * @since 1.0
 */
public function __construct()
{
  // XXX ���⤤�ä������
  date_default_timezone_set("Asia/Tokyo");
  $this->init();
}

/**
 * init
 *
 *
 * @param ������������
 * @return  ����ͤ�����
 * @access public
 * @since 1.0
 */
public function init()
{
  $this->set_year(0);
  $this->set_month(0);
  $this->set_day(0);
  $this->set_hour(0);
  $this->set_minute(0);
  $this->set_second(0);
  
  // �ǥե���ȥ���������ܻ���
  $this->set_zoneJST();
}

///////////////////////////////////////////////////
// ���å���

/**
 * ǯ�μ���
 *
 * @access public
 * @return int ǯ
 */
public function get_year()
{
  return $this->year_;
}

/**
 * ��μ���
 *
 *
 * @access public
 * @return int ��
 */
public function get_month()
{
  return $this->month_;
}

/**
 * ���μ���
 *
 * @access public
 * @return int ��
 */
public function get_day()
{
  return $this->day_;
}

/**
 * ���μ���
 *
 * @access public
 * @return int ��
 */
public function get_hour()
{
  return $this->hour_;
}

/**
 * ʬ�μ���
 *
 * @access public
 * @return int ʬ
 */
public function get_minute()
{
  return $this->minute_;
}

/**
 * �äμ���
 *
 * @access public
 * @return int ��
 */
public function get_second()
{
  return $this->second_;
}

/**
 * ʬ�μ���
 *
 * get_minute�ؤΥ�åѡ�
 * �񤯤Τ����ݤʤΤ�(���
 *
 */
public function get_min()
{
  return $this->get_minute();
}

/**
 * �äμ���
 *
 * get_second�ؤΥ�åѡ�
 * �񤯤Τ����ݤʤΤ�(���
 */
public function get_sec()
{
  return $this->get_second();
}

/**
 * ���ݥå�������μ���
 *
 * @access public
 * @return int ���ݥå�������(��)
 */
public function get_epoc()
{
  $t = sprintf("%4d-%02d-%02d %02d:%02d:%02d",
                $this->get_year(),
                $this->get_month(),
                $this->get_day(),
                $this->get_hour(),
                $this->get_minute(),
                $this->get_second()
              );
//print "get_epoc t is $t \n";
  return strtotime($t);
}

/**
 * ������μ���
 *
 * �ĥ��顼�θ������Ѥ��ƹԤ�
 * 0:������ �� 6:������ �ޤ�
 *
 * @access public
 * @return int 0:������ �� 6:������
 */
public function get_week()
{
  $yy = $this->get_year(); 
  $mm = $this->get_month();
  $dd = $this->get_day();
  
  if($mm == 1 || $mm == 2 ){
    $yy--;
    $mm += 12;
  }

  //
  return ( $yy + floor($yy/4) - floor($yy/100) + floor($yy/400) + floor((13*$mm+8)/5) + $dd )% 7;
}

/**
 * ����̾��ʸ����μ���
 *
 * ���Υ᥽�åɤǤ�full���ڥ���֤�
 * ��ʸ����ά�Τ��ۤ�������get_week_string_short���Ѥ���
 *
 * @access public
 * @return string full���ڥ������̾��ʸ����
 */
public function get_week_string()
{   
  return $this->wdy_[ $this->get_week() ];
}

/**
 * ����̾�Σ�ʸ��ά��ʸ����μ���
 *
 * ���Υ᥽�åɤǤϣ�ʸ��ά�Υ��ڥ���֤�
 * full���ڥ뤬�ۤ�������get_week_string���Ѥ���
 *
 * @access public
 * @return string ��ʸ��ά�Τ�����̾��ʸ����
 */
public function get_week_string_short()
{
  return $this->wdy3_[ $this->get_week() ];
}

/**
 * ��̾��ʸ����μ���
 *
 * ���Υ᥽�åɤǤ�full���ڥ���֤�
 * ��ʸ����ά�Τ��ۤ�������get_month_string_short���Ѥ���
 *
 * @access public
 * @return string full���ڥ�Ƿ�̾��ʸ����
 */
public function get_month_string()
{
  return $this->mon_[ $this->get_month() -1 ];
}

/**
 * ��̾��ʸ����μ���
 *
 * ���Υ᥽�åɤǤϣ�ʸ��ά�Υ��ڥ���֤�
 * full���ڥ뤬�ۤ�������get_month_string���Ѥ���
 *
 * @access public
 * @return string ��ʸ��ά�ΤǷ�̾��ʸ����
 */
public function get_month_string_short()
{   
  return $this->mon3_[ $this->get_month() -1 ];
}

/**
 * ��ꥦ�������֤�
 *
 * ��̩�ˤϥ�ꥦ����������.5���������Ρ�
 *
 * @access public
 * @return int ��ꥦ����
 */
public function get_julian()
{
  $yy = $this->get_year();
  $mm = $this->get_month();
  $dd = $this->get_day();
  
  if ($mm <= 2) {
    $yy --;
    $mm += 12;
  }

  //
  $jd = floor($yy*365.25) + floor($yy/400) - floor($yy/100) + floor(30.59*($mm-2)) + $dd +1721088;
//print "jd = $jd\n";

  //
  return $jd;
}

/**
 * �ե����ޥåȤ��줿���դ��֤�:yyyy/mm/dd hh:mm:ss
 *
 * @access public
 * @param string $sep ���դζ��ڤ�ʸ�����ǥե���Ȥ�'/'
 * @return string yyyy/mm/dd hh:mm:ss�η����˥ե����ޥåȤ��줿ʸ����
 */
public function get_string($sep = "/")
{
  $t = sprintf("%4d%s%02d%s%02d %02d:%02d:%02d",
                $this->get_year(),
                $sep,
                $this->get_month(),
                $sep,
                $this->get_day(),
                $this->get_hour(),
                $this->get_minute(),
                $this->get_second()
              );
  return $t;
}

/**
 * �ե����ޥåȤ��줿���դ��֤�:yyyy/mm/dd hh:mm:ss zone
 *
 * �����ॾ�����ɲä��줿get_string
 *
 * @access public
 * @param string $sep ���դζ��ڤ�ʸ�����ǥե���Ȥ�'/'
 * @return string yyyy/mm/dd hh:mm:ss zone�η����˥ե����ޥåȤ��줿ʸ����
 */
public function get_stringZ($sep = "/")
{
  $t = $this->get_string($sep) . ' ' . $this->zone_;
  return $t;  
}

/**
 * Cookie�Ѥ˥ե����ޥåȤ��줿���դ��֤�
 *
 * ����Ū�ˤ� "Wdy, DD-Mon-YY HH:MM:SS GMT" �Ȥ�������
 *
 * @access public
 * @return string Cookie�����˥ե����ޥåȤ��줿ʸ����
 */
public function get_string_for_cookie()
{
  $t = sprintf("%s, %02d-%02d-%4d %02d:%02d:%02d GMT",
                $this->get_week_string_short(),
                $this->get_day(),
                $this->get_month(),
                $this->get_year(),
                $this->get_hour(),
                $this->get_minute(),
                $this->get_second()
              );
  return $t;
}

/**
 * �᡼��إå��Ѥ˥ե����ޥåȤ��줿ʸ����
 *
 * �ºݤˤ�get_string_rfc2822()�ؤΥ����ꥢ��
 *
 * @access public
 * @return string �᡼��إå������˥ե����ޥåȤ��줿ʸ����
 */
public function get_string_for_mail() { return $this->get_string_for_rfc2822(); }

/**
 * RFC2822���ҷ���(�᡼��إå���)�˥ե����ޥåȤ��줿ʸ����
 *
 * �ե����ޥåȤ�Wdy, DD short-month YYYY HH:MM:SS zone
 *
 * @access public
 * @return string �᡼��إå������˥ե����ޥåȤ��줿ʸ����
 */
public function get_string_for_rfc2822()
{
  $t = sprintf("%s, %02d %s %4d %02d:%02d:%02d %s",
                $this->get_week_string_short(),
                $this->get_day(),
                $this->get_month_string_short(),
                $this->get_year(),
                $this->get_hour(),
                $this->get_minute(),
                $this->get_second(),
                $this->zone_
              );
  return $t;
}

/**
 * �貿���ܤ�����
 *
 * ���η���貿���ܤ��򻻽Ф���
 * �����ϡ�������ͤǤ���У������ˤʤ�Ϥ�
 *
 * @access public
 * @return int 1-5������ϣ����ܡ������ܤ򼨤���
 */
public function get_weeks_number_of_month()
{
  $dd = $this->get_day();
  $cpy = $this->deep_copy();
  
  $cpy->set_day(1);
  // ������ΰ��������������
  $week = $cpy->get_week();

  // ����
  return ((int)(($dd - 1 + $week)/7))+1;
}

///////////////////////////////////////////////////
// ���å���

/**
 * ǯ������
 *
 * @param int $arg ǯ
 * @access public
 */
public function set_year($arg)
{
  $this->year_ = $arg;
}

/**
 * �������
 *
 * @param int $arg ��
 * @access public
 */
public function set_month($arg)
{
  $this->month_ = $arg;
}

/**
 * ��������
 *
 * @param int $arg ��
 * @access public
 */
public function set_day($arg)
{
  $this->day_ = $arg;
}

/**
 * ��������
 *
 * @param int $arg ��
 * @access public
 */
public function set_hour($arg)
{
  $this->hour_ = $arg;
}

/**
 * ʬ������
 *
 * @param int $arg ʬ
 * @access public
 */
public function set_minute($arg)
{
  $this->minute_ = $arg;
}

/**
 * �ä�����
 *
 * @param int $arg ��
 * @access public
 */
public function set_second($arg)
{
  $this->second_ = $arg;
}

/**
 * ʬ������
 *
 * @param int $arg ʬ
 * @access public
 */
public function set_min($arg)
{
  return $this->set_minute($arg);
}

/**
 * �ä�����
 *
 * @param int $arg ��
 * @access public
 */
public function set_sec($arg)
{
  return $this->set_second($arg);
}

/**
 * ���ݥå������फ�����դ򥻥å�
 *
 * @param int $arg ���ݥå���
 * @access public
 */
public function set_epoc($arg)
{
  $t = localtime($arg, true);
//print "set_epoc t is \n";
//print_r($t);

  $this->set_year($t["tm_year"] + 1900);
  $this->set_month($t["tm_mon"] + 1);
  $this->set_day($t["tm_mday"]);
  $this->set_hour($t["tm_hour"]);
  $this->set_minute($t["tm_min"]);
  $this->set_second($t["tm_sec"]);
}

/**
 * ��ꥦ�������饻�å�
 *
 * @param int $jd ��ꥦ����
 * @access public
 */
public function set_julian($jd)
{
  $jd += 1; // +.5�ˡ�ü�����ڤ�ΤƤƤ�ʬ�Ǥ⤦.5�ǹ�סܣ�
  if ($jd < 2299161 ) {
    $a = $jd;
  } else {
    $x = floor(($jd - 1867216.25) / 36524.25);
    $a = $jd + 1 + $x - floor($x/4);
  }

  $b = $a + 1524;
  $c = floor(($b-122.1)/365.25);
  $d = floor(365.25 * $c);
  $e = floor(($b - $d) / 30.6001);

  $dd = $b - $d - floor(30.6001 * $e);
  if ($e < 14) {
    $mm = $e - 1;
    $yy = $c - 4716;
  } else {
    $mm = $e - 13;
    $yy = $c - 4715;
  }

  $this->set_year($yy);
  $this->set_month($mm);
  $this->set_day($dd);
}

/**
 * ʸ���󤫤�����
 *
 * �����б����Ƥ���Τϰʲ��ΤȤ��ꡣ
 * yyyymmdd
 * yyyy/mm/dd
 * yyyy-mm-dd
 *
 * @param string $base_string ���դ�ʸ����
 * @access public
 */
public function set_string($base_string)
{
  $yy = $mm = $dd = $h = $m = $s = 0; // �����
  $data = array();
  $tdata = array();

  // �ǡ������ڤ�ʬ��
  $iterator = preg_split('//', $base_string);
  $wk = "";
  foreach ($iterator as $s) {
    if (preg_match("/[0-9]/", $s)) {
      $wk .= $s;
    } else {
      if ($wk) {
        array_push($data, $wk);
         //print "$wk \n";
      }
      $wk = "";
    }
  }
  if ($wk) {
    array_push($data, $wk);
    // print "$wk \n";
  }

  // yyyymmdd�Υ����å�
  $wk = $data[0];
  if (8 === strlen($wk)) {
    // XXX ������������å���ɬ�פʤ������
    // ��ʸ���ǿ����ʳ��ξ��ɤΤߤ��ǡ������ѤʤΤ�
    // �����å��Ͼ�ά
    $yy = substr($wk, 0, 4);
    $mm = substr($wk, 4, 2);
    $dd = substr($wk, 6, 2);

    // ����������Ϥ�
    // �������Ƭ�ҤȤĤ����ʤ����Ϥ�
    $flg = 0;
    foreach ($data as $i) {
      if (0 == $flg) {
        $flg = 1;
      } else {
        array_push($tdata, $i);
      }
    }

  } else
  if (14 === strlen($wk)) {
    // XXX ������������å���ɬ�פʤ������
    // ��ʸ���ǿ����ʳ��ξ��ɤΤߤ��ǡ������ѤʤΤ�
    // �����å��Ͼ�ά
    // XXX ���Ľ�ʣ����ʤ� orz
    $yy = substr($wk,  0, 4);
    $mm = substr($wk,  4, 2);
    $dd = substr($wk,  6, 2);
    $h  = substr($wk,  8, 2);
    $m  = substr($wk, 10, 2);
    $s  = substr($wk, 12, 2);
  } else {
    // �̾�äƤ�����yyyymmdd�ʳ��Υ�����

    // �ʸ���λ����ִ�
    $wk = $data[1];
    if (preg_match("/^Jan/i", $wk)){
      $data[1] = "1";
    } else if (preg_match("/^Feb/i", $wk)) {
      $data[1] = "2";
    } else if (preg_match("/^Mar/i", $wk)) {
      $data[1] = "3";
    } else if (preg_match("/^Apr/i", $wk)) {
      $data[1] = "4";
    } else if (preg_match("/^May/i", $wk)) {
      $data[1] = "5";
    } else if (preg_match("/^Jun/i", $wk)) {
      $data[1] = "6";
    } else if (preg_match("/^Jul/i", $wk)) {
      $data[1] = "7";
    } else if (preg_match("/^Aug/i", $wk)) {
      $data[1] = "8";
    } else if (preg_match("/^Sep/i", $wk)) {
      $data[1] = "9";
    } else if (preg_match("/^Oct/i", $wk)) {
      $data[1] = "10";
    } else if (preg_match("/^Nov/i", $wk)) {
      $data[1] = "11";
    } else if (preg_match("/^Dec/i", $wk)) {
      $data[1] = "12";
    }

    // ����
    if (strlen($data[2]) == 4) {
      $yy = $data[2];
      $mm = $data[1];
      $dd = $data[0];
    } else {
      $yy = $data[0];
      $mm = $data[1];
      $dd = $data[2];
      if ($yy < 100) {
        $yy += 2000;
      }
    }

    // ����������Ϥ�
    $flg = 0;
    foreach ($data as $i) {
      if (3 > $flg) {
        $flg ++;
      } else {
        array_push($tdata, $i);
      }
    }

  } // ���ս�����

  // ���֤����
  if (isset($tdata[0])) {
    $wk = $tdata[0];
    if (strlen($wk) == 6) {
      $h = substr($wk, 0, 2);
      $m = substr($wk, 2, 2);
      $s = substr($wk, 4, 2);
    } else {
      $h = $tdata[0];
      $m = $tdata[1];
      $s = $tdata[2];
    }
  }

  //print "$yy : $mm : $dd \n";
  //print "$h : $m : $s \n";

  $this->set_year($yy);
  $this->set_month($mm);
  $this->set_day($dd);
  $this->set_hour($h);
  $this->set_minute($m);
  $this->set_second($s);
  
}

/**
 * ���ѥå���������ʸ���󤫤�����
 *
 * @param string $base_string ���ѥå����������շ���
 * @access public
 */
public function set_stringApache($base_string)
{
  $yy = $mm = $dd = $h = $m = $s = 0; // �����
  $matches = array();

  // ����ɽ���ǰ쵤���ڤ�Ф�
  // print "$base_string \n";
  if(preg_match('/([0-9][0-9])\/([a-zA-Z]+)\/([0-9][0-9][0-9][0-9]):([0-9][0-9]):([0-9][0-9]):([0-9][0-9])/',
                  $base_string,
                  $matches
                )){
    $yy = $matches[3];
    $wk = $matches[2];
    $dd = $matches[1];
    $h = $matches[4];
    $m = $matches[5];
    $s = $matches[6];
  }else{
    return array($yy, $mm, $dd, $h, $m, $s);
  }

  // �����ʬ��������Ѵ�
  if (preg_match("/^Jan/i", $wk)){
    $mm = "1";
  } else if (preg_match("/^Feb/i", $wk)) {
    $mm = "2";
  } else if (preg_match("/^Mar/i", $wk)) {
    $mm = "3";
  } else if (preg_match("/^Apr/i", $wk)) {
    $mm = "4";
  } else if (preg_match("/^May/i", $wk)) {
    $mm = "5";
  } else if (preg_match("/^Jun/i", $wk)) {
    $mm = "6";
  } else if (preg_match("/^Jul/i", $wk)) {
    $mm = "7";
  } else if (preg_match("/^Aug/i", $wk)) {
    $mm = "8";
  } else if (preg_match("/^Sep/i", $wk)) {
    $mm = "9";
  } else if (preg_match("/^Oct/i", $wk)) {
    $mm = "10";
  } else if (preg_match("/^Nov/i", $wk)) {
    $mm = "11";
  } else if (preg_match("/^Dec/i", $wk)) {
    $mm = "12";
  }

  $this->set_year($yy);
  $this->set_month($mm);
  $this->set_day($dd);
  $this->set_hour($h);
  $this->set_minute($m);
  $this->set_second($s);
}

/**
 * ���դ���������
 *
 * @access public
 */
public function set_matubi()
{
  $yy = $this->get_year();
  $mm = $this->get_month();
  
  $this->set_day($this->get_matubi());
}

/**
 * �����ॾ���������
 *
 * @param string $val �����ॾ�����ʸ����
 * @access public
 */
public function set_zone($val)
{
  $this->zone_ = $val;
}

/**
 * �����ॾ��������ܤ�����
 *
 * @access public
 */
public function set_zoneJST()
{
  $this->set_zone("+0900");
}

/**
 * �����ॾ���������ɸ���������
 *
 * @access public
 */
public function set_zoneGMT()
{
  $this->set_zone("GMT");
}

/**
 * �����ॾ��������ܤ�����
 *
 * @access public
 */
public function set_zoneJ()
{
  $this->set_zoneJST();
}

///////////////////////////////////////////////////

/**
 * �����˸��߻��������
 *
 * @access public
 */
public function set_now_date()
{
  $t = localtime(time(), true);

  $this->set_year($t["tm_year"] + 1900);
  $this->set_month($t["tm_mon"] + 1);
  $this->set_day($t["tm_mday"]);
  $this->set_hour($t["tm_hour"]);
  $this->set_minute($t["tm_min"]);
  $this->set_second($t["tm_sec"]);
}

/**
 * ������$age�ФǤ�����ָŤ��������򥻥å�
 *
 * @param int $age ǯ��
 * @access public
 */
public function set_birth_day_from($age)
{
  $this->set_now_date();
  $this->calculation_year(-($age+1));
  $this->calculation_day(1);  // 1���ץ饹
}

/**
 * ������$age�ФǤ�����ֿ������������򥻥å�
 *
 * @param int $age ǯ��
 * @access public
 */
public function set_birth_day_to($age)
{
  $this->set_now_date();
  $this->calculation_year(-($age));
}

/**
 * ���������ꤵ�줿���ͤ������������å�
 *
 * @return  boolean �����ʤ�true
 * @access public
 */
public function is()
{
  $yy = $this->get_year();
  $mm = $this->get_month();
  $dd = $this->get_day();

  // ǯ�����å�
  // ��Ǥʤ���Ф褷�Ȥ���
  if (0 > $yy) { return false; }

  // ������å�
  if (1 > $mm) { return false; }
  if (12 < $mm) { return false; }

  // �������å�
  if (1 > $dd) { return false; }
  $misoka = $this->get_matubi();
  if ($misoka < $dd) {
    return false;
  }

  return true;
}


////////////////////////////////
/**
 * �����μ���
 *
 * @return  int ���������顼�ξ��ϣ�
 * @access public
 */
// ��������Ƚ��
public function get_matubi()
{
  $yy = $this->get_year();
  $mm = $this->get_month();

  // ���
  if ($mm < 1) { return 0; }
  if ($mm > 12) { return 0; }

  // �����Ȥäƴ�ñ��Ƚ��
  $data = array("31", "", "31", "30", "31", "30", 
                "31", "31", "30", "31", "30", "31");

  if ($mm != 2) {
    $ret = $data[$mm - 1];
  } else {
    if (($yy%400)==0) {
      $ret = 29;
    } else if (($yy%100)==0) {
      $ret = 28;
    } else if (($yy%4)==0) {
      $ret = 29;
    } else {
      $ret = 28;
    }
  }

  return $ret;
}


/**
 * ���շ׻�
 *
 * ����ʬ�����ѹ�
 * ��������ñ�̤����
 *
 * @param string $unit ñ�̡�'year', 'month', 'day', 'hour' �Τ����줫
 * @param int $arg �������������
 * @access public
 */
public function calculation($unit, $arg)
{
  // ñ�̤��Ȥ˿���ʬ����Ԥ�
  if (!(strcasecmp("year", $unit))) {
    $this->calculation_year($arg);
  } else
  if (!(strcasecmp("month", $unit))) {
    $this->calculation_month($arg);
  } else
  if (!(strcasecmp("day", $unit))) {
    $this->calculation_day($arg);
  } else
  if (!(strcasecmp("hour", $unit))) {
    $this->calculation_hour($arg);
  }
}

/**
 * ����ʬ����ǯ���ѹ��ʥޥ��ʥ��ʤ�����
 *
 * @param int $arg �ѹ�����ǯ��
 * @access public
 */
public function calculation_year($arg)
{
  $this->set_year($this->get_year()+($arg));
}

/**
 * ����ʬ��������ѹ��ʥޥ��ʥ��ʤ�����
 *
 * @param int $arg �ѹ�������
 * @access public
 */
public function calculation_month($arg)
{
  // �Ȥꤢ���������η��­������
  $wk = $this->get_month()+($arg);
  //
  $ywk = $this->get_year();

  // �ޥ��ʥ��ξ��ν���
  while($wk < 1) {
    $wk += 12;
    $ywk --;
  }
  // 13��ʾ�ξ��ν���
  while($wk > 12) {
    $wk -= 12;
    $ywk ++;
  }

  // ����
  $this->set_year($ywk);
  $this->set_month($wk);
}


/**
 * ����ʬ�����������ѹ��ʥޥ��ʥ��ʤ�����
 *
 * @param int $arg �ѹ���������
 * @access public
 */
public function calculation_day($arg)
{
  // ��ꥦ�����˲û����ƥ��å�
  $this->set_julian($this->get_julian()+($arg));
}

/**
 * ����ʬ�������֤��ѹ��ʥޥ��ʥ��ʤ�����
 *
 * @param int $arg �ѹ��������
 * @access public
 */
public function calculation_hour($arg)
{
  // �ä������դΥ��ݥå�������λ���
  $arg_epoc = 60 * 60 * $arg;
  
  // ���ߤΥ��ݥå�������˲û�
  $new_epoc = $arg_epoc + $this->get_epoc();
  
  // ���å�
  $this->set_epoc($new_epoc);
}

/**
 * ������Ʊ���ʤ�true;
 *
 * ���դ���֤���פ�������true
 *
 * @param calendar $cal ��٤륫���������֥�������
 * @return  boolean Ʊ���ʤ�true
 * @access public
 */
public function equal($cal)
{
  if(!$this->equal_date($cal) || !$this->equal_time($cal)){
    return false;
  }
  
  return true;
}
/**
 * ���դ�Ʊ���ʤ�true
 *
 * @param calendar $cal ��٤륫���������֥�������
 * @return  boolean Ʊ���ʤ�true
 * @access public
 */
public function equal_date($cal)
{
  // ���줾��㤦�ʤ�false
  if($this->get_year() != $cal->get_year()){
    return false;
  }
  
  if($this->get_month() != $cal->get_month()){
    return false;
  }
  
  if($this->get_day() != $cal->get_day()){
    return false;
  }
  
  return true;
}

/**
 * ���֤�Ʊ���ʤ�true
 *
 * @param calendar $cal ��٤륫���������֥�������
 * @return  boolean Ʊ���ʤ�true
 * @access public
 */
public function equal_time($cal)
{
  // ���줾��㤦�ʤ�false
  if($this->get_hour() != $cal->get_hour()){
    return false;
  }
  
  if($this->get_minute() != $cal->get_minute()){
    return false;
  }
  
  if($this->get_second() != $cal->get_second()){
    return false;
  }
  
  return true;
}

/**
 * ���ȤΥ��ԡ������
 *
 * @return calendar copy���줿���󥹥���
 * @access public
 */
public function deep_copy()
{
  // �Ȥꤢ�����饤��copy
  return clone $this;
}

/**
 * ���󥹥������ymd������ǯ���׻�
 *
 * XXX �������ϥ��󥹥�����ˤ���Ȥ���
 *
 * @access public
 */
public function make_age(){

  // ���߻���μ���
  $now_time = new calendar;
  $now_time->set_now_date();

  // �Ȥꤢ�����绨�Ĥ�ǯ�𻻽�
  $age = $now_time->get_year() - $this->get_year();

  // 1��ʬ����Ĵ��
  if ($now_time->get_month() < $this->get_month()) {
    $age --;
  } else
  if ($now_time->get_month() == $this->get_month()) {
    if ($now_time->get_day() < $this->get_day()) {
      $age --;
    }
  }

  //
  return $age;
}

//private:
private $year_;
private $month_;
private $day_;
private $hour_;
private $minute_;
private $second_;
private $zone_;

private $mon_ = array("January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"); 

private $mon3_ = array("Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul" , "Aug", "Sep ", "Oct", "Nov", "Dec");

private $wdy_ = array("Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"); 

private $wdy3_ = array("Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat");

};
?>