<?php BoxTop("CVS"); ?>

�� ����������� ������������ �� Audacity �� �������� ���������
<a target=_top href="http://www.cvshome.org">CVS</a>, ��� Concurrent Versions
System [������� �� ���������� �� ��������� ������]. ��������
<a target=_top href="http://cvs.sourceforge.net/cgi-bin/viewcvs.cgi/audacity/audacity-src/">���</a>, �� ��
������ �������� ��� � ����������� �� CVS.

<p>
<h3>���������: ������ 1.2 � ����������:</h3>
��� ������ ��������� ���� �� Audacity, ������ 1.2.x, ������ �� ��������
<tt>-r AUDACITY_1_2</tt> ��� ���������� ��� ��������� �� ������� �� CVS. ����� �� �������� �������� ���� (HEAD), ����� ���� �� ����� ����� ����������, ������ �������� ������ �� ������ 1.3.0.

<p><h3>���� ���� �� ������ � Audacity ���� CVS:</h3>
�� ������ �� �������� ��� �� Audacity ����������� ������ �� CVS, �� �� ���������
����������� (branch) �� CVS �� ����� ��������. ���� ���� ��� ��������
�������������, ����������� ������� �� CVS �� �� ������ �� ������� �������� ��
�������������� � ���������� ������������ �� Audacity. �� �� �������� ������ ��
�������� ���, ��������� ������� ��������.

<h4>�������� ������ �� CVS ���� ������, ���������� �� ��������� ���:</h4>
<p>�������� �������� �� ��������� ��� (������ �� ���� ���!):<br>
<ul><tt>cvs -d:pserver:anonymous@cvs.audacity.sourceforge.net:/cvsroot/audacity
login </tt><br></ul>
� ��������� Enter, ������ ������ �������� �� ������.

<p>���� ����, <b>�� �� ��������� ���-������ ����������� (1.3.0)</b> (��� �� ���� ���):
<br>
   <ul><tt>cvs -z3 -d:pserver:anonymous@cvs.audacity.sourceforge.net:/cvsroot/audacity co
audacity</tt></ul>
��� <b>�� ���������� ����������� (1.2.0)</b> (�� ���� ���):<br>
   <ul><tt>cvs -z3 -d:pserver:anonymous@cvs.audacity.sourceforge.net:/cvsroot/audacity co -r AUDACITY_1_2 audacity</tt></ul>
��� <b>�� ������ ���� 1.0 (1.0.0)</b> (�� ���� ���):<br>
   <ul><tt>cvs -z3 -d:pserver:anonymous@cvs.audacity.sourceforge.net:/cvsroot/audacity co -r audacity-0_9-branch audacity-old</tt></ul>


<p> ������ ���� �� ��������� �� ���������� <tt>CVSROOT</tt> �� ������������ ��������
<tt>:pserver:anonymous@cvs.audacity.sourceforge.net:/cvsroot/audacity</tt>
(����� ��-����).<br>
���� ����, <b>�� �� ��������� ���������� ���������� ����������� (1.3.0)</b>, ��������<br> 
   <ul><tt>cvs checkout audacity</tt></ul>
���, <b>�� ���������� ����������� (1.2)</b>, �������� <br>
   <ul><tt>cvs checkout -r AUDACITY_1_2 audacity</tt></ul>
���, <b>�� ������� ����������� 1.0 </b>, �������� <br>
   <ul><tt>cvs checkout -r audacity-0_9-branch audacity-old</tt></ul>   <ul><tt>cvs checkout -r audacity-0_9-branch audacity-old</tt></ul>

<p>�� �� �������� �������� �� ������������ <tt>CVSROOT</tt> �� ������������, ���� ��
���������� ��������� ���� �� ��������� ������������� ��� ���� �� �������� �������:
<h5>� bash (bourne shell), �� ���� ���:</h5>
<ul><tt>export
CVSROOT=:pserver:anonymous@cvs.audacity.sourceforge.net:/cvsroot/audacity</tt><br></ul>
<h5>� csh � ������������ ��, �� ���� ���:</h5>
<ul><tt>setenv CVSROOT
:pserver:anonymous@cvs.audacity.sourceforge.net:/cvsroot/audacity</tt><br></ul>

<hr width="80%">

<h4>�������� ������ �� CVS ���� �������� ������</h4>
�� �������� ������ ���� wincvs, maccvs ��� gcvs (�������� ��
<a target=_top href="http://cvsgui.org">cvsgui.org</a>), ������ �� ��������� �� ������������
<tt>CVSROOT</tt> (� ��������� Admin|Preferences) ��������
<tt>:pserver:anonymous@cvs.audacity.sourceforge.net:/cvsroot/audacity</tt>
� �� ����� �� ������ (authentication) �� �������� "pserver" ��� "Password".
����� �� �������, �� � ���������� Globals �� ���������� �������� Preferences
������ "Checkout read-only (CVSREAD)" �� � ���������. ���� ���� �������� login �
��������� Enter �� ����������� �� ������ (�� � ""). ������, �������� "Create|Checkout module",
�������� ��������������� �� ��������� �� ������������� � ��������� ���������� ��-����
� ���������� �� �������� �����������. ��� �������� ��������� �� ������, ���������
���� ������������ <tt>CVSROOT</tt> �� �������� � ��������� - ����� ���� �� �� �����, ��� ��� �������� ���������� ������� �� ���������� ��������.

<p>
<b>�� �� �������� ���������� ���������� ����������� (1.3.0):</b><br>
� ���������� �������� "Checkout Settings" �������� ���� ��� �� �����
<tt>audacity</tt>. ��������� "OK" � ������������� �� ���� ������� �����������
�� ����� ��������.
<p>
<b>�� �� �������� ���������� ����������� (1.2.0): </b><br>
� ���������� �������� "Checkout Settings" �������� ���� ��� �� �����
<tt>audacity-old</tt>. �����, �� ���������� "Sticky options", ���������
������ "Retrieve rev./tag/branch (-r)" � �������� <tt>AUDACITY_1_2</tt> �
���������� ���� �� ����. ��������� "OK" � ������������� �� ���� ������� �����������
�� ����� ��������.

<p>
<b>�� �� �������� ������� ����������� (1.0):</b><br>
� ���������� �������� "Checkout Settings" �������� �� ��� �� ����� <tt>audacity-old</tt>. �����, �� ���������� "Sticky options", ��������� ������ "Retrieve rev./tag/branch (-r)" � �������� <tt>audacity-0_9-branch</tt> � ���������� ���� �� ����. ��������� "OK" � ������������� �� ���� ������� �����������
�� ����� ��������.

<hr width="80%">
�� ��� �������� � CVS ������? ���������, ���������� <a href="">Introduction
to
CVS</a> [��������� � CVS] �� ���� ������ (Jim Blandy), <a target=_top href="http://www.cvshome.org/new_users.html">CVS for new
users</a> [CVS �� ���� �����������] �� ��� ������ (Bob Arnson), ��� �������� ���������� �� CVS �� ����� <a target=_top href="http://www.cvshome.org/">www.cvshome.org</a>.
��-�������� ���������� � �������� � �������, ���������������� �� ������ GPL, �� ������� �� CVS �� ���� ����� (Karl
Fogel) �� <a target=_top href="http://cvsbook.red-bean.com/cvsbook.html">cvsbook.red-bean.com</a>, ��� "�����������" <a target=_top href="http://www.cvshome.org/docs/manual">�����������</a> �� ��� ���������� (Per Cederqvist).


<p>�� ����� ��������� �� �������� ��� sourceforge.net ���� CVS ����� �������������� �� Source Forge ��
����������� <a target=_top href="http://sourceforge.net/docman/display_doc.php?docid=763&group_id=1">Unix</a>,
<a target=_top href="http://sourceforge.net/docman/display_doc.php?docid=766&group_id=1">Microsoft Windows</a> � <a target=_top href="http://sourceforge.net/docman/display_doc.php?docid=2973&group_id=1">MacOS
(����� OS X)</a>.

<hr width="80%">

<p>
<b>��� �����������:</b>

</p>

<p>� Audacity �� ���������� ����� ����������, ������ �� ����� ����.
����� �� ��� �� ������� �� ���� �������, �� �� �� ���������� �� ������ ������
���������. ������ ����������� �������� ��� �� ������ ������ ���������� � CVS.
��� ����� ������ �� ������:
</p>
<p>��� ��� ���������: 'audacity-src', ����� ������� ����� ������� �� ��� ���, �
'lib-src', ����� ������� �������� ��� �� ������������ ����� ����������.
�� �� �� ��������� ������������ ����� Audacity � ������������, ������������ �� ��
���������� �������� �� �� 'lib-src'. �� Unix ������ �� ��������� �������������
�� ����� �� ������������, ����������� ���� ����������� �� ��������� ����������.
�������� 'configure --help', �� �� ������ ���������� �����������.
</p>
<p>
� ����, ��� ������ �� ������� ������, ����������� �������� ��� �� ������������,
��������� ������ 'audacity', ����� �� ����� audacity-src ������ ��� ������������ ��
lib-src ���� ������������� �� 'audacity'.
</td>
</tr>
</table>
</p>

<?php BoxBottom(); ?>
