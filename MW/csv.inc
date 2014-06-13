<?php
// +-----------------------------------------------------------------+
// | ���⥸�塼��̾
// |    CSV�򰷤����饹��
// | ��������
// |    y_ogura
// | ����������
// |    ����        ������̾    ��������
// |    2006/09/12 y_ogura ��������
// |    2006/09/26 y_ogura EOF��ľ�������Ԥξ�硢�ѡ�����ǡ������������˶��ǡ���������Τǽ���
// | ������
// |    $Id$
// +-----------------------------------------------------------------+
// | Copyright (c) 2006 Quinland CO.,LTD All rights reserved
// +-----------------------------------------------------------------+

require_once("grid_data.inc"); 
require_once("file_util.inc"); 

/*
 * CSV���饹
 */
class csv extends grid_data {

	/*
	 * CSV�ѥ��Υ��å���
	 */
	public function set_path($path="") {

		if (0 < strlen($path)) {
			$this->path_ = $path;
		} else {
			echo "class name is:" . get_class($this). ":file path is null!!\n";
			exit;
		}

		// �ѡ�����¹�
		$this->parse();
	}
	
	/*
	 * CSV�ѥ��Υ��å���
	 */
	public function get_path() {

		// �ե�����ѥ����ꤷ�Ƥ���ʤ��Ȳ��ˤ�Ǥ��ؤ�
		if (0 < strlen($this->path_)) {
			return $this->path_;
		} else {
			echo "class name is:" . get_class($this). ":file path is null!! please call method set_path(path)\n";
			exit;
		} 

	}
	
	/*
	 * ���󥹥ȥ饯��
	 */
	public function __construct() {
		$this->init();
	}

	/*
	 * init
	 */
	public function init() {
		// �Ƥ�á��
		parent::init();
	}

	/*
	 * �ᥤ�����
	 * ��1.CSV�ե������ɤ߹���
	 *   2.�ѡ����¹�
	 */
	private function parse() {
		
		// CSV�ե������ɤ߹���
		// XXX �Ȥꤢ����UTF8�����Ȥǥ����å���
		$data = file_util::read_file_to_utf8($this->get_path());

		// CSV�ѡ�������
		$obj_csv_p = new csv_parse();
		
		// CSV�ǡ������å�
		$obj_csv_p->set_data($data);
		
		// CSV�ѡ����¹ԡ���
		$obj_csv_p->parse();
		
		// grid_data���饹������
		$this->set_data($obj_csv_p->get_parsed_data());
	}

	/**
	 * CSV�ѥ�
	 */
	private $path_;

} // end of csv class

/**
 * CSV�ǡ����Υѡ�����Ǥ���饹
 */
class csv_parse {

	/*
	 * �ѡ������ǡ����Υ��å�
	 */
	public function set_data($d) { $this->data_string_ = $d; }

	/*
	 * �ѡ������ǡ����Υ��å�
	 */
	private function get_data() { return $this->data_string_; }

	/*
	 * �ѡ�����ǡ����Υ��å�
	 */
	public function set_parsed_data($d) { $this->data_array_ = $d; } 

	/*
	 * �ѡ�����ǡ����Υ��å�
	 */
	public function get_parsed_data() { return $this->data_array_; }

	/*
	 * �ѡ���
	 */
	public function parse() {

		// CSV������֥�����������&�ǡ������å�
		// �ʹߤ�CSV������֥������Ȥ˼½������Ǥ
		// XXX set_data()�ǥѡ����ޤǼ¹Ԥ���褦�ˤ���
		// XXX set_data()��parse()��ʬ���������ɤ���
		$csv_wk = new csv_p_work();
		$csv_wk->set_data($this->get_data());

		// �ѡ�����ǡ�����ʬ���ݻ�
		// get_parsed_data() �ǥѡ�����ǡ������������٤ˡ�
		$this->set_parsed_data($csv_wk->get_parsed_data());
	}

	/**
	 * �ѡ������ǡ���
	 */
	private $data_string_;

	/**
	 * �ѡ�����ǡ���
	 */
	private $data_array_ = array();

} // end of csv_parse class


/**
 * CSV�ǡ����Υ�����饹
 *   ����(�⡼��)�ˤ�äơ��ѡ������֥������Ȥ򥳡���
 *   csv_p��csv_parse��ά
 */
class csv_p_work {

	/*
	 * ���󥹥ȥ饯��
	 */
	public function __construct() {
		$this->init();
	}

	/*
	 * ���
	 */
	public function init() {
		// �������ܥ��֥�����������
		$this->objs_["set_normal"]  = new csv_p_set_normal();		// �̾�⡼��
		$this->objs_["set_crlf"]    = new csv_p_set_crlf();			// ���ԥ⡼��
		$this->objs_["set_esp"]     = new csv_p_set_esp();			// ���������ץ⡼��
		$this->objs_["set_esp_chk"] = new csv_p_set_esp_chk();	// ���������ץ����å��⡼��
		
		// ����⡼�ɤ��̾�⡼�ɤ򥻥å�
		$this->set_normal_mode();
		
		// XXX �ե����������β����к�
		$this->empty_flg_ = true;
	}

  /*
   * �ǡ��������뤫�ɤ���Ƚ��
   * XXX empty�᥽�åɤʤΤǡ֤ʤ����true��
   */
	public function is_empty() { return $this->empty_flg_; }

	/*
	 * ����(�⡼��)�Υ��å�
	 */
	public function set_mode($s) { $this->mode_ = $s; }

	/*
	 * ����(�⡼��)�Υ��å�
	 */
	public function get_mode() { return $this->mode_; }

	/*
	 * �̾�⡼�ɤΥ��å�
	 */
	public function set_normal_mode() { $this->set_mode("set_normal"); }

	/*
	 * ���ԥ⡼�ɤΥ��å�
	 */
	public function set_crlf_mode() { $this->set_mode("set_crlf"); }

	/*
	 * ���������ץ⡼�ɤΥ��å�
	 */
	public function set_esp_mode() { $this->set_mode("set_esp"); }

	/*
	 * ���������ץ����å��⡼�ɤΥ��å�
	 */
	public function set_esp_chk_mode() { $this->set_mode("set_esp_chk"); }

	/*
	 * �ѡ������ǡ����Υ��å�
	 */
	public function set_data($d) {
		$this->data_string_ = $d;
		$this->set_length();		// �ǡ���Ĺ���ݻ�
		$this->parse();					// �ѡ����¹�
	}

	/*
	 * �ѡ������ǡ����Υ��å�
	 */
	public function get_data($p="") {
		if (0 < strlen($p)) {
			return $this->data_string_[$p];
		} else {
			return $this->data_string_;
		}
	}

	/*
	 * �ѡ�����ǡ����Υ��å�
	 */
	public function get_parsed_data() { return $this->data_array_; }

	/*
	 * �������ܥ��֥������ȤΥ��󥹥��󥹤��֤�
	 */
	public function get_parse_obj() {	return $this->objs_[$this->get_mode()];	}

	/*
	 * 1ʸ�����å�
	 */
	public function get_char() { return $this->get_data($this->pos_); }

	/*
	 * �ǡ���Ĺ���ݻ�
	 */
	public function set_length() { $this->len_ = strlen($this->get_data()); }

	/*
	 * �ǡ���Ĺ���֤�
	 */
	public function get_length() { return $this->len_; }

	/*
	 * 1ʸ���򥹥ȥå�
	 */
	public function push_char() {
		$this->stac_ .= $this->get_char();
		// �ǡ������ͤޤ줿�����ݻ����뤿�ᡢfalse�򥻥å�
		$this->empty_flg_ = false;
	}	
	/*
	 * 1�ե�����ɤ�ʸ����򥹥ȥå�
	 *   ���줬ί�ޤäƤ����ȡ�1�쥳����ʬ�Υǡ����ˤʤ�
	 */
	public function push_col() {

//print "push col stac is " . $this->stac_ . "\n";

		$this->col_[] = $this->stac_;	// 1�ե������ʬ��ʸ������ͤù���
		$this->stac_  = "";
	}

	/*
	 * �ѡ�����ǡ���������
	 */
	public function push_datas() {

//print "in push data " ."\n";

		$this->data_array_[] = $this->col_;	// 1�쥳����ʬ�Υǡ������ͤù���
		$this->col_ = array();
		// �ԥǡ��������ꤷ���Τǡ��ǡ����ξ��֤�empty���᤹
		$this->empty_flg_ = true;
	}

	/*
	 * �Хåե����ꥢ
	 */
	public function buf_clear() {
		$this->push_col();
		$this->push_datas();
	}

	/*
	 * Iterate�Ѥ�fetch�᥽�å�
	 *   ʸ���ݥ��󥿤����ǡ���Ĺ�ʾ�ʤ鵶���֤�
	 */
	public function fetch() {

		// ʸ���ݥ��󥿤Υ��󥯥����
		$this->inc_pos();

		// Iterate��λȽ��
		if ($this->get_length() <= $this->pos_) {
			return false;
		}

		return true;
		
	}

	/*
	 * ʸ���ݥ��󥿤��Ŀʤ��
	 */
	public function inc_pos() { $this->pos_++ ; }

	/*
	 * ʸ���ݥ��󥿤����᤹
	 */
	public function dec_pos() { $this->pos_-- ; }

	/*
	 * �ѡ���
	 */
	public function parse() {

		// �ǡ���Ĺ�����֤�󤷤ƥѡ���
		while ($this->fetch()) {

//print "before mode:" . $this->get_mode() . "\n";
//print "char:" . $this->get_char() . "\n";

			$this->get_parse_obj()->parse($this);
			
//print "after  mode:" . $this->get_mode() . "\n";
		}

		// XXX �ǡ������ͤޤ�Ƥ���Ȥ������Хåե����ꥢ
		// XXX ����Ƚ�̵꤬���ȡ����Ԥǽ���äƤ�Ȥ����Զ��ȯ����
		if (! ($this->is_empty()) ) {
			$this->buf_clear();
		}
	}

	/**
	 * ����(�⡼��)
	 */
	private $mode_;

	/**
	 * �������ܥ��֥������ȳ�Ǽ����
	 */
	private $objs_ = array();

	/**
	 * �ѡ������ǡ���
	 */
	private $data_string_;

	/**
	 * �ѡ�����ǡ���
	 *   ����
	 */
	private $data_array_ = array();

	/**
	 * �����å��ǡ���(1�ե������ʬ��ʸ������ݻ�)
	 */
	private $stac_;

	/**
	 * �ԥ����å��ǡ���(1�쥳����ʬ�Υǡ������ݻ�)
	 */
	private $col_;

	/**
	 * ʸ���ݥ���
	 */
	private $pos_ = -1;
	
	/**
	 * �ǡ���Ĺ
	 */
	private $len_ = -1;
	
	/**
	 * Empty�ե饰
	 */
	private $empty_flg_;



} // end of csv_p_work class

/**
 * �̾�⡼��
 *   �Ǥ����Ū�ʾ��֤򰷤����ʲ��ε�ư��Ԥ���
 *     ','     cell�ζ��ڤ���̣����ʸ����Ƚ�Ǥ���
 *     '"'     ���������ץ⡼�ɤؤΥ⡼�����ؤ�Ԥ�
 *     '\r'    ���Ԥ�����CR-LF�β�ǽ����ͤ���CRLF�⡼�ɤ��ڤ��ؤ���
 *     '\n'    ���ԡ���ԤΥǡ����ν�����Ƚ�Ǥ���
 *     any     �̾�Υǡ����Ȥߤʤ�
 */
class csv_p_set_normal {

	/*
	 * �̾�⡼�ɤΥѡ���
	 */
	public function parse($wk) {

		switch ($wk->get_char()) {
			// cell���ڤ�
			case ",":
				$wk->push_col();				// 1�ե������ʬ��ʸ����򥹥ȥå�
				$wk->set_normal_mode();	// �̾�⡼�ɤ�
				break;
			// ���������ץ⡼�����ؤ�
			case "\"":
				$wk->set_esp_mode();		// ���������ץ⡼�ɤ�
				break;
			// CRLF�⡼�����ؤ�
			case "\r":
				$wk->set_crlf_mode();		// CRLF�⡼�ɤ�
				break;
			// �쥳���ɶ��ڤ�
			case "\n":
				$wk->buf_clear();				// �ԥǡ���������Хåե����ꥢ
				$wk->set_normal_mode();	// �̾�⡼�ɤ�
				break; 
			// any(�̾�ǡ���)
			default:
				$wk->push_char();				// 1ʸ���򥹥ȥå�
				$wk->set_normal_mode();	// �̾�⡼�ɤ�
		}

	}

} // end of class

/**
 * ���ԥ⡼��
 *   CR-LF�����ꤷ�Ƥ���⡼�ɡ��ʲ��ε�ư��Ԥ���
 *     '\n'    '\r\n'�Ǥ��ä����ᡢ�����ǰ�ԤΥǡ����ν�����Ƚ��
 *     any     '\r\n'�ǤϤʤ��ä����ᡢ���ߤΥǡ������̾�⡼�ɤǺƽ���
 */
class csv_p_set_crlf {

	/*
	 * ���ԥ⡼�ɤΥѡ���
	 */
	public function parse($wk) {

		switch ($wk->get_char()) {
			// �쥳���ɶ��ڤ�(\r\n�����顣)
			case "\n":
				$wk->buf_clear();				// �ԥǡ���������Хåե����ꥢ
				$wk->set_normal_mode();	// �̾�⡼�ɤ�
				break; 
			// any(�̾�⡼�ɤ˺����ᤷ)
			default:
				$wk->buf_clear();				// (\r���ä�����)�ԥǡ���������Хåե����ꥢ
				$wk->dec_pos();					// �̾�⡼�ɺƽ����ΰ١��ݥ����᤹
				$wk->set_normal_mode();	// �̾�⡼�ɤ�
		}

	}
	
} // end of class

/**
 * ���������ץ⡼��
 *   '"'��','������뤿��Υ⡼�ɡ�','�Ϥ����Υǡ����Ȥ��ư�����
 *   �ʲ��ε�ư��Ԥ���
 *     '"'     �⡼�����ؤ��ǡ������狼��ʤ����ᡢ���������ץ����å��⡼�ɤ��ڤ��ؤ�
 *     any     �̾�Υǡ����Ȥߤʤ�
 */
class csv_p_set_esp {

	/*
	 * ���������ץ⡼�ɤΥѡ���
	 */
	public function parse($wk) {

		switch ($wk->get_char()) {
			// ���������ץ����å��⡼�ɤ��ڤ��ؤ�
			case "\"":
				$wk->set_esp_chk_mode();	// ���������ץ����å��⡼�ɤ�
				break; 
			// any(�̾�ǡ���)
			default:
				$wk->push_char();					// 1ʸ���򥹥ȥå�
				$wk->set_esp_mode();			// ���������ץ⡼�ɤ�
		}

	}
	
} // end of class

/**
 * ���������ץ����å��⡼��
 *   ���������ץ⡼����˽ФƤ���'"'��������뤿��Υ⡼��
 *   �ʲ��ε�ư��Ԥ���
 *     '"'     '""'�ȤʤäƤ��뤿�ᡢ�ǡ�����'"'���ɲá��⡼�ɤϥ���������
 *     any     ���������ץ⡼�ɤ����̾�⡼�ɤؤ��ڤ��ؤ��ؼ��Ȥߤʤ���
 *             �⡼�ɤ��̾���ڤ��ؤ������ߤΥǡ������̾�⡼�ɤǺƽ���
 */
class csv_p_set_esp_chk {

	/*
	 * ���������ץ����å��⡼�ɤΥѡ���
	 */
	public function parse($wk) {

		switch ($wk->get_char()) {
			// �ǡ����Ȥ��Ƥ�'"'�򥹥ȥå�
			case "\"":
				$wk->push_char();							// 1ʸ���򥹥ȥå�
				$wk->set_esp_mode();					// ���������ץ⡼�ɤ�
				break; 
			// any �̾�⡼�ɤؤ��ڤ��ؤ�
			default:
				$wk->dec_pos();								// �̾�⡼�ɺƽ����ΰ١��ݥ����᤹
				$wk->set_normal_mode();				// �̾�⡼�ɤ�
		}

	}

} // end of class
