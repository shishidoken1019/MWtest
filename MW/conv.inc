<?php
/**
 * CONV(�ִ�)���饹
 *
 * ������֥ƥ�ץ졼�ȥ��󥸥�ס�
 *
 * @package magicweapon
 * @link http://www.grid-works-guild.net/MagicWeapon/ MagicWeapon
 * @access  public
 * @author  Michiaki Wuzawa <wuzawa@m-fr.net>
 * @create  $LastChangedDate$
 * @version $Revision$
 **/

class f_conv {
// public:

public function __construct()
{
  $this->init();
}

//
public function init()
{
  $this->toku_ = array();
  $this->toku_yes_ = array();
  $this->toku_no_ = array();
  $this->mono_ = array();
  $this->fuku_ = array();
}

/**
 * �ƥ����������ǡ�������
 *
 * ʸ����������ǡ�����������롣
 * stdout�˽Ф��ʤ�T_put�Τۤ�����
 *
 * @access public
 * @return string �����ǡ���
 */
public function T_string() {
$ret = "";

  $ret .= "mono dictionary\n";
  foreach($this->mono_ as $name => $value) {
    $ret .= "  " . $name . ": " . $value . "\n";
  }
  $ret .= "\n";

  $ret .= "multi dictionary\n";
  foreach($this->fuku_ as $name => $value) {
    $ret .= "  " . $name . ": " . get_class($value) . "\n";
  }
  $ret .= "\n";

  $ret .= "tokusyu dictionary\n";
  foreach($this->toku_ as $name => $value) {
    $ret .= "  " . $name . "\n";
    $ret .= "	yes : " . $this->toku_yes_[$name] . "\n";
    $ret .= "	 no : " . $this->toku_no_[$name] . "\n";
    $ret .= "	data: ";

    foreach($this->toku_[$name] as $n => $v) {
      $ret .= $v . " , ";
    }
    $ret .= "\n";
  }
  //
  $ret .= "T_put Fin\n";

  //
  return $ret;
}

/**
 * �ƥ����������ǡ�������
 *
 *
 * @access public
 */
public function T_put() {
  echo $this->T_string();
}

/**
 * �ü��ִ�����Ͽ
 *
 * ���chekbox��select��radio�ʤ��Ѥ�����
 *
 * @access public
 * @param string $name �ؼ���̾
 * @param string $y �ǡ�����������ͤ�ͭ��Ȥ�����������
 * @param string $n �ǡ�����������ͤ�̵���Ȥ�����������
 * @param array $d �ǡ�������
 * @return boolean �������꤬�����false
 */
public function monoDicToku($name, $y, $n, $d) {
  if ("" === $name) {
    return false;
  }

  // �ǡ���������ǤϤʤ��Ȥ���̵���������ˤ��Ƥߤ�
  if (is_array($d)) {
    $da = $d;
  } else {
  // XXX �ǡ��������ʤ�����ˤ��ʤ�
      if ("" !== $d) {
      $da = array($d);
    } else {
      $da = $d;
    }
  }

  // ���å�
  $this->toku_[$name] = $da;
  $this->toku_yes_[$name] = $y;
  $this->toku_no_[$name] = $n;

  //
  return true;
}

/**
 * ñ�ִ���Ͽ
 *
 * @access public
 * @param string $name �ؼ���̾
 * @param string $value ���ꤹ����
 * @return boolean �������꤬�����false
 */
public function monoDic($name, $value) {
  if ("" === $name) {
    return false;
  }
  //
  $this->mono_[$name] = $value;

  //
  return true;
}

/**
 * ʣ�ִ���Ͽ
 *
 * @access public
 * @param string $name �ؼ���̾
 * @param ���饹���󥹥��� $obj �¹Ԥ����٤����饹
 * @return boolean �������꤬�����false
 */
// ʣ�ִ���
public function multiDic($name, $obj) {
  if ("" === $name) {
    return false;
  }
  //
  $this->fuku_[$name] = $obj;

  //
  return true;
}

/**
 * �ִ��»�
 *
 * @access public
 * @param string $ret �ִ���Ȥ�ʸ����
 * @return string �ִ����ʸ���󡣥��顼�ξ���ʸ����
 */
function conv($ret) {
  //
  if ("" === $ret) {
    return "";
  }

  // ʣ�ִ�����
//print "base is ($ret)\n";
  while( 1 == (preg_match("/(.*?)[\$]{3}([0-9a-zA-Z_-]*)[:]{0,1}(.*?)[\$]{3}(.*)/s", $ret, $wk)) ) {
    $before = $wk[1];
    $f_name = $wk[2];
    $f_param = $wk[3];
    $after = $wk[4];
//print "after is ($atfer)\n";
    if ( 1 == (preg_match( "/(.*?)[\$]{3}[\/]" . $f_name . "[\$]{3}(.*)/s", $after, $wk))) {
      $base_body = $wk[1];
//print "function name is $f_name($f_param)\n";
//print "base body is ($base_body)\n";
//print "after data is ($wk[2])\n";
      // ����
      // �ؿ���¸�ߤ���Фޤ魯
      $buf = "";
      if (isset($this->fuku_[$f_name])) {
        $f = $this->fuku_[$f_name];
//print "call function $f_name($f_param)($f)<BR>\n";

//print_r($f);
        // ���֥������ȤΥ᥽�åɤ�call
        $buf = $f->m_conv($base_body, $f_param);
      } else {
//print "not find : function $f_name($f_param)\n";
      }

      // ­������
      $ret = $before . $buf . $wk[2];
//print "add is ($ret)\n";
    } else {
      // ������ʬ��̵�뤷�ƻĤ�
//print "no match\n";
      $ret = $before . $after;
    }
//print "multi: ret is ($ret)\n";
  }

  // �ü�ñ�ִ��ν���
  while( 1 == (preg_match("/(.*)\*\*\*([0-9a-zA-Z_-]*):{0,1}(.*?)\*\*\*(.*)/s", $ret, $wk)) ) {
    $before = $wk[1];
    $name = $wk[2];
    $p = "" . $wk[3];
    $after = $wk[4];

    // �֤��
    $flg = "";
    if (isset($this->toku_[$name])) {
      if (is_array($this->toku_[$name])) {
        foreach ($this->toku_[$name] as $wk) {
//print "toku wk is $wk\n";
          if (0 == strcmp($wk, $p)) {
            $flg = "OK";
            break;
          }
        }

        // Ƚ��
        if ("OK" == $flg) {
          $ret = $before . $this->toku_yes_[$name] . $after;
        } else {
          $ret = $before . $this->toku_no_[$name] . $after;
        }
      }

    } else {
      // �ǡ������ʤ�����̵��
      $ret = $before . $after;
    }
//print "toku: ret is ($ret)\n";
  }

  // ñ�ִ�
  while( 1 == (preg_match("/(.*)%%%([0-9a-zA-Z_-]*)%%%(.*)/s", $ret, $wk)) ) {
//print "change $wk[2] <BR> \n";
    // �ѿ���
    if (isset($this->mono_[$wk[2]])) {
      $ret = $wk[1] . $this->mono_[$wk[2]] . $wk[3];
    } else {
      // XXX ���顼�ɤ����롩
      $ret = $wk[1] . $wk[3];
    }
//print "mono: ret is ($ret)\n";
  }

  // XXX ñ�ִ����ɲ�
  $ret = preg_replace("/###/", "%%%", $ret);
  // XXX �ü��ִ��Ѥ��ɲ�
  $ret = preg_replace("/@@@/", "***", $ret);

  //
  return $ret;
}


// private:
//
private $toku_;	// �ü��ִ��ѥǡ���
private $toku_yes_;	// �ü��ִ��ѥǡ���:�ͤ����פ����Ȥ�������ǡ���
private $toku_no_;	// �ü��ִ��ѥǡ���:�ͤ����פ��ʤ��Ȥ�������ǡ���

//
private $mono_;	// ñ�ִ��ѥǡ���

//
private $fuku_;	// ʣ�ִ��ѥǡ���

} // end of class
