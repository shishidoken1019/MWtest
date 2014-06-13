<?php

require_once('file_util.inc');
require_once('pair.inc');


////////////////////////////
// ��¤�ηϥ��饹
////////////////////////////

// ���ȥå��ǡ����ѥ��饹
class lexical_analysis_stock_data
{
//public:
public function get_data() { return $this->data_; }
public function push_data($n, $v)
{
//print "push data ($n, $v) \n";
  $wk = new pair;
  $wk->set($n, $v);
  $this->data_[] = $wk;
}

//
public function push_isdata_from_buf($n)
{
  if ("" != $this->get_buf()) {
    $this->push_data($n, $this->get_buf());
    $this->set_buf("");
  }
}
//
public function push_data_from_buf($n)
{
  $this->push_data($n, $this->get_buf());
  $this->set_buf("");
}

//
public function add_buf($c) { $this->buf_ .= $c; }
public function set_buf($s) { $this->buf_ = $s; }
public function get_buf() { return $this->buf_; }

//private:
private $data_ = array();	// vector<pair *> �ȡ�����ǡ����켰
private $buf_ = "";		// �Хåե��ǡ���
} // end of class


// ���ϸ��ǡ����ݻ��ѥ��饹
class lexical_analysis_data
{
//public:
public function __construct()
{
  $this->init();
}

//
public function init()
{
  $this->set_data("");
}

//
public function set_length($i) { $this->length_ = $i; }
public function get_length() { return $this->length_; }

//
public function get_data() { return $this->data_; }
public function set_data($s)
{
  $this->data_ = $s;
  $this->set_length(strlen($s));
  $this->set_count(-1);	// fetch�ߤ����֥��󥯥ꤷ�ƻȤ��פΤ�-1��������
}

// ������Ƚ��
// ���ߤ�iterator�����󥿤�length�ȤΥ����������å�
public function is_length()
{
  if ($this->get_length() <= $this->get_count()) {
    // �Ǥ���������
    return false;
  }
  //
  return true;
}

//
public function set_count($i) { $this->count_ = $i; }
public function get_count() { return $this->count_; }

// ���󥯥����
// XXX ��ư��is_length��äȤ�����
public function inc_count() {
  $this->set_count($this->get_count() + 1);
  return $this->is_length();
}

// ���ǥǡ����μ���
public function get_element() { return $this->data_[$this->get_count()]; }
// XXX ��ʸ�����ü���
public function get_element_next(){ return $this->data_[$this->get_count()+1]; }


//private:
private $data_;		// �ǡ���
private $count_;	// ���ߤ�iterator������
} // end of class




////////////////////////////
// �������饹
////////////////////////////

// ���⡼����Σ�ʸ��������ν���ô��
class lexical_analysis_engine_unit
{
//public:
//
public function set_next_mode($s) { $this->next_mode_ = $s; }
public function set_processing_list($a) { $this->processing_list_ = $a; }

//
public function get_my_char() { return $this->my_char_; }

//
public function set_my_char($s)
{
  // XXX ����Ƚ��
  if ("'" == $s[0]) {
    // ��ʸ�������ڤ�ȴ��
    $this->my_char_ = $s[1];
  } else {
    // �������оݤˤ���
    $this->my_char_ = $s;
  }
//print "my char is ... " . $this->my_char_ . "\n";
}

//
public function set_processing_string($s)
{
  // &���ڤ��ڤ�
  $this->set_processing_list( explode("&", $s) );
//print_r ($this->processing_list_);
}

//
public function run($data_obj, $stock_obj)
{
  ///////////////////////////
  // �����򤹤�
  // XXX ʣ���ν�����¸�ߤ�����
  ///////////////////////////
  foreach($this->processing_list_ as $processing) {
//print "���� : $processing\n";
    // error����
    if ("error" == $processing) {
      //throw new Exception("lexical analysis error!!");
      throw new Exception( "error!! (" . $this->next_mode_ . ")" );
    }

    // no��̵����
    if ("no" == $processing) {
      continue;
    }

    // ­�����߷�
    if ("+" == $processing[0]) {
      // +char��my_char��buf��­������
      if ("+char" == $processing) {
        $stock_obj->add_buf($data_obj->get_element());
      } else {
        // +'x'�����ꤵ�줿ʸ����buf��­������
        // XXX ��ʸ�����ꡣ���ʤ�Ӥ�����
        $stock_obj->add_buf($processing[2]);
      }
    }

    // push:'name',data��'name'�˥ǡ���(data�ʤ�buf������)��push
    //   �⤷data��ʬ��̵����ʤ�ֶ�ʸ���װ�����push
    if ( preg_match("/^push/", $processing)) {
      // �ޤ���ʬ��
      $push_data = explode(",", $processing);
      $push_data[] = "";

      // ̾�������
      // XXX ����⤫�ʤ�Ӥ�
      $abuf = explode("'", $push_data[0]);
      $push_name = $abuf[1];
      
      // ���ȥå����֥����ؤΤ֤�����
      if ("data" == $push_data[1]) {
        // �Хåե��֤����ߤĤĥ��ꥢ�⤷�Ƥ���
        $stock_obj->push_data_from_buf($push_name);
      } else if ("isdata" == $push_data[1]) {
        // �Хåե��֤����ߤĤĥ��ꥢ�⤷�Ƥ���
        $stock_obj->push_isdata_from_buf($push_name);
      } else {
        // XXX data����ʤ����̵���Ƕ�ʸ���ˤ��Ƥ���
        $stock_obj->push_data($push_name, "");
      }
    }

  }

  // ���Υ⡼�ɤ��������ƽ����
  return $this->next_mode_;
}

//private:
private $my_char_;	// ��ʬ���Ȥ�ʸ������ʸ����+char��
private $next_mode_;	// ���Υ⡼����ʸ����
private $processing_list_;	// ����ʸ����:����
	// &�Ƕ��ڤä�ʣ���ν�����¸�ߤ�����
	// no��̵����
	// +char��my_char��buf��­������
	// +'x'�����ꤵ�줿ʸ����buf��­������
	// push:'name',data��'name'�˥ǡ���(data�ʤ�buf������)��push
	//   �⤷data��ʬ��̵����ʤ�ֶ�ʸ���װ�����push
}



// ���⡼�ɤ�����ν���ô��
class lexical_analysis_engine
{

// ʸ���󤫤�ɬ�פ������ڤ�Ф��Ƽ���
public function set_mode_name_string($s)
{
  // �Ȥꤢ�������֤��ڤ�
  $abuf = explode("\t", $s);

  // XXX �����ܤ����Ǥ�����̵�Ѥ�
  $this->mode_name_ = $abuf[0];
//print "mode name = " . $this->mode_name_ . "\n";
}
public function get_mode_name() { return $this->mode_name_; }

// ��ʸ�������ѥ��󥹥��󥹤�����
public function set_processing_data($s)
{
//print "processing data is $s \n";
  // �ޤ�ʬ��
  $abuf = explode("\t", $s);
  // XXX error�Τ���˥��Х��Ȥʽ������ɲ�
  $abuf[] = "";

  // �����ܤ����Ǥ���Ƭ��# ������Ф���ϥ����ȤʤΤǽ�λ
  if ("#" == $abuf[1][0]) {
//print "this string is comment\n";
    return ;
  }

  // ���󥹥��󥹺���
  $obj = new lexical_analysis_engine_unit;

  // ����
  $obj->set_my_char($abuf[1]);
//print "my char is " . $obj->get_my_char() . "\n";
  $obj->set_processing_string($abuf[2]);
//print "processing string is " . $abuf[2] . "\n";
  $obj->set_next_mode($abuf[3]);
//print "next mode is " . $abuf[3] . "\n";

  // �����ѤΥ��󥹥��󥹤Ȥ�����Ͽ
  $this->processing_obj_[ $obj->get_my_char() ] = $obj;
  //
  if ("hs" == $obj->get_my_char()) {
    $this->hs_flg_ = true;
//print "hs flg is true\n";
  }
  //
  if ("crlf" == $obj->get_my_char()) {
    $this->crlf_flg_ = true;
//print "crlf flg is true\n";
  }
  //
  return ;
}


public function analysis($data_obj, $stock_obj)
{
  // �оݤȤʤ��ʸ������Ф�
  $itr = $data_obj->get_element();

  // ����ʸ���Υ����å�
  $do_obj = NULL;
  if (isset($this->processing_obj_[$itr])) {
    // ¸�ߤ�������ʤΤǽ������֥��������
    $do_obj = $this->processing_obj_[$itr];
  } else {
    // �ü������hs �ۥ磻�ȥ��ڡ���
    // XXX ���Ԥϡִޤޤʤ�����������
    if ( $this->hs_flg_ ) {
      // ���ڡ��� // ����
      if ((' ' == $itr) || ("\t" == $itr)) {
        $do_obj = $this->processing_obj_['hs'];
      }
    }
    // �ü������crlf ����
    if ( $this->crlf_flg_ ) {
      // LF�ΤߤΥ�����
      if ('\n' == $itr) {
        $do_obj = $this->processing_obj_['crlf'];
      } else if ('\r' == $itr) {
        // CRLF���θ
        if ('\n' == $data_obj->get_element_next()) {
          $data_obj->inc_count();
        }
        $do_obj = $this->processing_obj_['crlf'];
      }
    }
  }

  // ���Ƴ������ʤ����any�Υ��֥������Ȥ������Ƥ�
  if (is_null($do_obj)) {
    $do_obj = $this->processing_obj_['any'];
  }

  // �ǡ�����
  // XXX �����ͤ�modeʸ������֤�
  return $do_obj->run($data_obj, $stock_obj);
}

//
private $mode_name_;		// mode̾���褦�ϼ�ʬ���Ȥ�̾��
private $processing_obj_;	// �����ѥ��֥�������
				// map<name, lexical_analysis_engine_unit *>
private $hs_flg_ = false;	// �⤷hs��������󤬤����true
private $crlf_flg_ = false;	// �⤷crlf��������󤬤����true
} // end of class


// �ᥤ�󥯥饹
class lexical_analysis
{
//public:
// XXX get��private�Ǥ�����ͤ���
private function get_config_file() { return $this->config_fn_; }
public function set_config_file($s) { $this->config_fn_ = $s; }

//
public function set_data($s) { $this->data_ = $s; }
// XXX get��private�Ǥ�����ͤ���
private function get_data() { return $this->data_; }
//
public function set_data_file($filename)
{
  // �ե�����ǡ�������������Ĥ��ͤù���
  $this->set_data(file_util::read_file($filename));
}


// ����ᥤ������å�
// vector<pair *> parse(void);
function parse($data = "")
{
  /////////////////////////
  // config��ʬ��
  /////////////////////////
  // �ǡ����β���
  $fh = fopen($this->get_config_file(), "r");
  $mode = "";
  if ($fh) {
    while (!feof($fh)) {
      $wk = fgets($fh);
      // �������Ԥ���
      $wk = rtrim($wk);
//print "config line is \n\t$wk \n";
//print "$wk \n";

      // �����Ԥʤ鼡��
      if (preg_match("/^$/", $wk)) {
//print "empty ... next!!\n";
        continue;
      }

      // ��Ƭ�� # ��������ϥ����ȤʤΤǼ�
      if ("#" == $wk[0]) {
//print "comment ... next!!\n";
        continue;
      }

      // ���ơ������Ǥ⤹�ä�
//print "$wk \n";
      // �������⡼�ɤ��ݤ�
      if ("\t" != $wk[0]) {
        // �������⡼�ɺ���
        $obj = new lexical_analysis_engine;
        $obj->set_mode_name_string($wk);

        // �����ȤȤ��Ϥ�����������mode̾�����
        $mode = $obj->get_mode_name();

        // �����Ͽ�����å�
        if (isset($this->analysis_obj_list_[$mode])) {
//print "�����Ͽ������ ( $mode ) \n";
        } else {
          // �⡼����Ͽ
          $this->analysis_obj_list_[$mode] = $obj;
        }
      } else {
        // ���ߤΥ⡼�ɤ��Ф��ƥץ�������Ͽ
        $this->analysis_obj_list_[$mode]->set_processing_data($wk);
      }
    }
    fclose($fh);
  }

  /////////////////////////
  // ����
  /////////////////////////
  // �ǡ����μ���
  if ("" == $data) {
    $data = $this->get_data();
  }

  // �ǡ����ݻ��ѤΥ��饹�˥ǡ������Ǽ
  // XXX ���ˣ�ʸ�����ϤȤ����ꤨ��Τ�
  $data_obj = new lexical_analysis_data;
  $data_obj->set_data($data);

  // �֤�󤷤ĤĲ���
  $stock_obj = new lexical_analysis_stock_data;
  $mode = "base";

  try {
    while( $data_obj->inc_count() ) {
//print $data_obj->get_element() . "\n";

      // ʬ��
      // XXX �����Ϥ��Ǥ��뤳�Ȥ������
      // XXX �Ĥ��Ǥ˼��Υ⡼��̾������������Ǥ����Τ���
//print "mode is $mode \n";
      $mode = $this->analysis_obj_list_[$mode]->analysis($data_obj, $stock_obj);
    }
  } catch (Exception $e) {
    // ���顼�ʤ�����̵�Ѥǽ�λ��
// XXX
print "get exception!!!\n";
print $e->getMessage() . "\n";
print $e->getCode() . "\n";
print $e->getFile() . "\n";
print $e->getLine() . "\n";
    //exit;
    return NULL;
  }
  
  // vector<pair *>
  return $stock_obj->get_data();
}


//private:
private $config_fn_;	// config�ե�����̾
private $data_;		// �����оݤΥǡ���
private $length_;	// $data_��Ĺ����strlen�Ǽ���

//
private $analysis_obj_list_;	// ʬ�ϥ��󥹥��󥹤����󡧥ϥå����
				// map<name, lexical_analysis_engine *>
} // end of class

