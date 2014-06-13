<?php

/**
 * Internet Message Format��header�ѥ��饹
 *
 * �Ȥꤢ�������󥳡��ɤ�iso-2022jp����
 *
 * @package magicweapon
 * @link http://www.grid-works-guild.net/MagicWeapon/ MagicWeapon
 * @access  public
 * @author  Michiaki Wuzawa <wuzawa@m-fr.net>
 * @create  $LastChangedDate$
 * @version $Revision$
 **/

require_once('security.inc');
require_once('multimap.inc');
require_once('multibyte.inc');
require_once('calendar.inc');

class internet_message_format_header_fields {

public function __construct()
{
  //
  $this->init();
}

//
public function init()
{
  $this->header_ = new multimap;
  $this->m_ = new multibyte;
  $this->m_->set_from_encoding_unknown();
  $this->m_->set_to_encoding_jis();

  // �ǥե��������
  // mail read�ͤ���ȼ�­��
  $this->set_content_type('text/plain; charset=iso-2022-jp');
  $this->set_date_now();
  $this->make_message_id();
  $this->_set_header('Mime-Version', '1.0');
  $this->_set_header('Content-Transfer-Encoding', '7bit');
  $this->_set_header('X-Mailer', 'MagicWeapon');
}

//
protected function get_multibyte() { return $this->m_; }

/**
 * ñ��إå�������
 *
 * ��ʣ���ʤ�(�Ϥ�)�Υإå�������
 * ��ʣ������硢��񤭤����
 *
 * @access protected
 * @param string $n �ե������̾
 * @param string $v �ե��������ʸ
 * @return boolean �������ä���false
 */
protected function _set_header($n, $v)
{
  //
  if ( ("" === $n)||("" === $v) ) {
    return false;
  }
  $v = security::sanitize_header_fields_data($v);
  // �������ܤ��Ƥߤ�
  $itr = $this->header_->find($n);
//var_dump($itr);
  //if (empty($itr)) {
  if (is_null($itr)) {
    // �ʤ����insert
    $this->header_->insert($n, $v);
//print "add_once insert\n";
  } else {
    // ����о��
    $this->header_->real($itr)->set_second($v);
//print "add_once update\n";
  }
  return true;
}

/**
 * ��ʣ��ǽ�إå�������
 *
 * @access protected
 * @param string $n �ե������̾
 * @param string $v �ե��������ʸ
 * @return boolean �������ä���false
 */
protected function _push_header($n, $v)
{
  if ( ("" === $n)||("" === $v) ) {
    return false;
  }
  $v = security::sanitize_header_fields_data($v);
  $this->header_->insert($n, $v);
  return true;
}

/**
 * ���ɥ쥹�ʳ�������������������ޤॢ�ɥ쥹�κ���
 *
 * name <email@add.ress> �ߤ����ʷ������������
 *
 * @access protected
 * @param string $address email���ɥ쥹
 * @param string $sender_name ������̾��
 * @return string �������ä����ʸ��
 */
protected function _make_internet_address($address, $sender_name = "")
{
  if ("" === $address) {
    return "";
  }
  if ("" === $sender_name) {
    //return $address;
    return '<' . $address . '>';
  }
  // ��̾����ʬ�򤴤ˤ��
  $s = $this->_b_encoding($sender_name) . ' <' . $address . '>';

  //
  return $s;
}

// B-Encoding
protected function _b_encoding($s)
{
  // XXX ���ʤ�̵����� orz
  $s = mb_convert_encoding($s, "ISO-2022-JP", 'eucjp-win,sjis-win,SJIS,EUC-JP,JIS,UTF-8,ASCII');
  $s = '=?ISO-2022-JP?B?' . base64_encode($s) . '?=';
  return $s;
}

// XXX
protected function _b_decoding($s)
{
  // XXX mb_encode_mimeheader�԰¤ʤΤ�̤����
  $mobj = new multibyte;
  $mobj->set_euc();
  // XXX ɬ����ʬȴ����decode����ʸ�������ɤ��ѹ�
  $s = $mobj->convert(base64_decode(substr($s, 16, (strlen($s) - 18))));
  // XXX �������󥳡��ɡĳ��������ʤ��Ȥͤ���
  return $s;
}

//_get_header($n)
//_get_header_array($n)

// �Ƽ�إå�����
/**
 * To������
 *
 * ʣ������Ϥ��٤ƤĤߤ�����
 *
 * @access public
 * @param string $a To�����ꤹ��᡼�륢�ɥ쥹
 * @param string $n ���ɥ쥹���յ�����̾��ɽ��(��ά��)
 */
public function push_to($a, $n = "")
  { return $this->_push_header('To', $this->_make_internet_address($a, $n)); }

/**
 * Cc������
 *
 * ʣ������Ϥ��٤ƤĤߤ�����
 *
 * @access public
 * @param string $a Cc�����ꤹ��᡼�륢�ɥ쥹
 * @param string $n ���ɥ쥹���յ�����̾��ɽ��(��ά��)
 */
public function push_cc($a, $n = "")
  { return $this->_push_header('Cc', $this->_make_internet_address($a, $n)); }

/**
 * Bcc������
 *
 * ʣ������Ϥ��٤ƤĤߤ�����
 *
 * @access public
 * @param string $a Bcc�����ꤹ��᡼�륢�ɥ쥹
 * @param string $n ���ɥ쥹���յ�����̾��ɽ��(��ά��)
 */
public function push_bcc($a, $n = "")
  { return $this->_push_header('Bcc', $this->_make_internet_address($a, $n)); }

/**
 * Mail From������
 *
 * @access public
 * @param string $a Mail From�����ꤹ��᡼�륢�ɥ쥹
 * @param string $n ���ɥ쥹���յ�����̾��ɽ��(��ά��)
 */
public function set_from($a, $n = "")
  { return $this->_set_header('From', $this->_make_internet_address($a, $n)); }


/**
 * Subject������
 *
 * @access public
 * @param string $v Subject
 */
public function set_plain_subject($v)
  { return $this->_set_header('Subject', $this->_b_encoding($v)); }
/**
 * Subject������
 *
 * set_plain_subject�ؤΥ����ꥢ��
 *
 * @access public
 * @param string $v Subject
 */
public function set_subject($v) { return $this->set_plain_subject($v); }
/**
 * ���󥳡��ɤ��줿Subject������
 *
 * ����ޤ�Ȥ�ʤ��Ϥ����ѡ������Ѥ��ʡ�
 *
 * @access public
 * @param string $v ���󥳡��ɤ���Ƥ���Subject
 */
public function set_encoded_subject($v)
  { return $this->_set_header('Subject', $v); }


// �����դȤꤢ���������Ƚ񤫤ʤ���
public function set_sender($v) { return $this->_set_header('Sender', $v); }
public function set_return_path($v) { return $this->_set_header('Return-Path', $v); }
public function set_reply_to($v) { return $this->_set_header('Reply-to', $v); }
public function set_in_reply_to($v) { return $this->_set_header('In-reply-to', $v); }
public function set_references($v) { return $this->_set_header('References', $v); }
public function set_comments($v) { return $this->_set_header('Comment', $v); }
public function set_keywords($v) { return $this->_set_header('Keywords', $v); }

/**
 * Date������
 *
 * ����Ȥ���ꡢset_date_now�Ǹ��߻������ꤷ���ۤ�����
 * ������ꤷ�����ʤ�calendar���󥹥��󥹺�ä� set_date_from_calendar ����
 *
 * @access public
 * @param string $v ���դ�������ʸ�����
 */
public function set_date($v) { return $this->_set_header('Date', $v); }

/**
 * ���߻����Date������
 *
 * @access public
 */
public function set_date_now()
{
  //
  $cobj = new calendar;
  $cobj->set_now_date();
  return $this->set_date_from_calendar($cobj);
}

/**
 * ���ꤵ�줿Date������
 *
 * calendar���󥹥��󥹤ǻ���
 *
 * @access public
 * @param calendar_obj $cobj Date�����ꤷ�������վ�����ĥ��󥹥���
 */
public function set_date_from_calendar(calendar $cobj)
{
  // ����ɽ��
  // Thu, 02 Aug 2001 10:45:23 +0900
  $t = sprintf("%s, %02d %s %4d %02d:%02d:%02d +0900",
                $cobj->get_week_string_short(),
                $cobj->get_day(),
                $cobj->get_month_string_short(),
                $cobj->get_year(),
                $cobj->get_hour(),
                $cobj->get_minute(),
                $cobj->get_second()
              );
  //
  $this->set_date($t);
}

/**
 * message-id������
 *
 * �ºݤˤϤ������make_message_id�Τۤ�����
 *
 * @access public
 * @param string $v ���ꤷ������å�����ID
 */
public function set_message_id($v)
  { return $this->_set_header('Message-id', $v); }

/**
 * message-id�κ���������
 *
 * �ʲ������
Message-Id: <20071211100546.8D46D330785@news.mixi.jp>
Message-Id: <20071211093113.694833E066D@news.mixi.jp>
Message-Id: <20071211072747.A61121C067@roccho.hatena.ne.jp>
Message-ID: <-1616970909.1197355023898.JavaMail.root@atitms02>
Message-ID: <20071211134137.595.2097.edm@emml005.nikkeibp.co.jp>
Message-Id: <475dd1fc-0007326a-ec71beaac573b087fc8f84181b5d3a01-52218@mailer08.bulk.ogk.yahoo.co.jp>
Message-Id: <200712102007.lBAK73Di026290@kym01a.rnet.or.jp>

         $message_id = '<' . $REMOTE_PORT . '.';
         if (!$hide_addr) {
            $message_id .= $REMOTE_ADDR . '.';
         }
         $message_id .= time() . '.squirrel@' . $SERVER_NAME .'>';

��å��������̻Ҥ��������ۥ��ȤΥɥᥤ��̾
(�ޤ��� IP ���ɥ쥹�Υ�ƥ��ɽ��)�� "@" ��
��¦���֤�����¦�����ջ���Ȥ��Υ����ƥ��
���Ѳ�ǽ�ʥ�ˡ�����(�����餯�������󥷥���)
���̻�(�㤨�Хץ����� ID)�Ȥ��֤��Τ��ɤ���ˡ
�Ǥ��롣
 *
 * @access public
 */
public function make_message_id()
{
  // FQDN����
  // XXX
  $domain = trim(`hostname`);

  // ���ּ���
  list($usec, $sec) = explode(" ", microtime());
  $usec = (int)($usec * 1000 * 1000);

  // �ץ�����ID
  $pid = getmypid();

  // ­������Ǥߤ�
  $s = sprintf("<%d.%d.%d@%s>", $sec, $usec, $pid, $domain);

  //
  $this->set_message_id($s);
}

/**
 * Content-type������
 *
 * @access public
 * @param string $v ���ꤷ����content-type
 */
public function set_content_type($v) { return $this->_set_header('Content-type', $v); }

// ����Ȥ碌�����ʤ�����񤫤ʤ��衩
public function get_all_headers()
{
  // XXX ���������ɤ����뤫�ͤ���
  $ret = "";
  for($itr = $this->header_->begin(); $itr != $this->header_->end(); $itr ++) {
    // ʸ�������
    $name = $this->header_->real($itr)->get_first();
    $value = $this->header_->real($itr)->get_second();
    // XXX ���ԥ����� au���Ȱ㤦����Ȥ� orz
    $ret .= $name . ': ' . $value . "\r\n";
  }
  //
  return $ret;
}


//private:
private $header_;
private $m_;

} // end of class
