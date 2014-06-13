<?php
/**
 * �󼡸��ǡ����򰷤����饹
 */
class grid_data {

	/*
	 * ���󥹥ȥ饯��
	 */
	public function __construct() { $this->init(); }

	/*
	 * init
	 */
	public function init() {
		$this->data_array_ = array();
		$this->max_line_num_ = -1;
		$this->fetch_init();
	}

	/*
	 * �ѡ�����ǡ����Υ��å�
	 *   ���åȤ��줿�ǡ��������ǿ����ݻ�
	 */
	public function set_data($d) {
		$this->data_array_   = $d;
		$this->max_line_num_ = count($this->data_array_);
	}

	/*
	 * �ѡ�����ǡ����Υ��å�
	 * XXX ��ǽ�ʤ�����ֻȤ��ʡס���
	 */
	public function get_data() { return $this->data_array_; }

	// -----------------------------------------------------------------------

	/*
	 * ����ԤΥǡ������֤�
	 *   ¸�ߤ��ʤ��Ԥ���ꤵ�줿���ϡ�false���֤�
	 */
	// array function get_line($i)
	public function get_line($i = -1) {

		// ���꤬�ʤ����fetch�Υ��󥽡���Ԥ��֤�
		if (-1 == $i) {
			$i = $this->get_pos_row();
		}
 		// �ԥǡ������֤�
		if (isset($this->data_array_[$i])) {
			return $this->data_array_[$i];
		} else {
			return false;
		}
	}

	/*
	 * ���ꥫ���Υǡ������֤�
	 *   ¸�ߤ��ʤ���������ꤵ�줿���ϡ�false���֤�
	 * XXX �᥽�å�̾�ˤ��ä��ꤳ�ʤ���
	 */
	// string function get_pos($row, $col)
	public function get_pos($row = -1, $col = -1) {

		// ���꤬�ʤ����fetch�Υ��󥽡���Ԥ��֤�
		if (-1 == $row) {
			$row = $this->get_pos_row();
		}
		if (-1 == $col) {
			$col = $this->get_pos_col();
		}

		// �����Υǡ������֤�
		if (isset($this->data_array_[$row][$col])) {
			return $this->data_array_[$row][$col];
		} else {
			return false;
		}
	}

	/*
	 * ����Կ����֤�
	 */
	// integer function get_max_row()
	public function get_max_row() { return $this->max_line_num_; }

	// --------------------------------------------------
	// Fetch��
	// --------------------------------------------------

	// fetch�� init �᥽�åɷ�
	public function fetch_init() {
		$this->fetch_init_row();
		$this->fetch_init_col();
	}
	public function fetch_init_row() {
		$this->pos_row_ = -1;
	}
	public function fetch_init_col() {
		$this->pos_col_ = -1;
	}

	// fetch�� �ݥ������᥽�åɷ�
	public function inc_pos_row() { $this->pos_row_++; }
	public function inc_pos_col() { $this->pos_col_++; }
	public function get_pos_row() { return $this->pos_row_; }
	public function get_pos_col() { return $this->pos_col_; }

	// fetch �ᥤ��
	/////////////////////
	// �Ԥ�fetch
	// boolean public function fetch_row();
	public function fetch_row() {

		$this->inc_pos_row();

		// XXX �Կ�ʬ�롼�פ����齪λ
		if ($this->get_pos_row() > $this->get_max_row()) { 
			return false;
		}

		// �Ԥ��ư�����顢��Υݥ��󥿤���������
		$this->fetch_init_col();
		
		return $this->get_line();
	}

	/*
	 * ���fetch
	 */
	// string public function fetch_col()
	public function fetch_col() {

		$this->inc_pos_col();

		// XXX
		if (!(isset($this->data_array_[$this->get_pos_row()][$this->get_pos_col()]))) { 
			return false;
		}
		return $this->data_array_[$this->get_pos_row()][$this->get_pos_col()];
	}

	/**
	 * �ǡ���
	 */
	private $data_array_;

	/**
	 * �ǡ��������Կ�
	 */
	private $max_line_num_;

	/**
	 * �ԥݥ���
	 */
	private $pos_row_;
	
	/**
	 * ��ݥ���
	 */
	private $pos_col_;

} // end of grid_data class

/*
$test_array = array(
0=>array(0=>"������",1=>"������"),
1=>array(0=>"������",1=>"eeee")
);

$obj = new grid_data();
$obj->set_data($test_array);

while($obj->fetch_row()) {

	$col = array();

	while($aaa = $obj->fetch_col()) {

		echo "col:$aaa\n";

	}

}

echo "------------------\n";
$obj->fetch_init();
while ($line = $obj->fetch_row()) {
	print_r($line);
}

*/


