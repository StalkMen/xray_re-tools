===S.T.A.L.K.E.R. *.spawn compiler/decompiler for every build from 1465===

���� ��������� ������: 23 �������� 2011

������: ������ acdc ������������ ��� ���������� all.spawn/level.spawn �� ������ �����, ������� � 1465. ����������
� ������ ������ ������ ����� �� ���������� cse_abstract ������ �������� ������ (version � script_version), 
� ������������ � ��� � ������������� �����. �������������� �������� � ������� ������������ �� game.graph.

��������� ����� ����������������� ������� ��������������� ������ �� ����� ������ � ������. �� ������ ������
�������������� ��� ������ ��������, ������� �� 2�� ����� ��.

��������� ��������� ������� �����. ��� ���������� ���������� ����� �������� ����.
����� "unknown section" ��������. 

��� ���������� ������ ����������� � ������ stkutils ��������� ������.

�������������:
������� all.spawn (��� level.spawn) � game.graph � ����� � ����������, ������� ������ (������� ����),
���������� ������, ��������� �����. ���� �������������� level.spawn, game.graph, ��������, �� �����.
����� game.graph �� ����� � ������ �� � �� - ��� �� ���� ����� � �����.

===[���������� ������]===
�������:  acdc [-d spawn_file] [-o outdir] [-l] [-g graph_dir] [-scan <scan_dir>]

-d <spawn_file> - ���� �� ������.
-o <outdir> - ���� �� �����, ���� ���� ����������� �����. ���� �� ������, ����� ��������������� � ����� � acdc
-l - ���� ��� ������������ level.spawn
-scan <scan_dir> - ���� �� ����� �������� �������� ���� (���� �������������� ���). ���� �� ������ ��������� 
��������� ��� �������. ��� �������, ����� �������� ����� config � ����� � acdc � ��������� 
� ����� ������: -scan config\
-g <graph_dir> - ���� �� game.graph. ���� ���� � ����� � acdc, ���� ����� �� ���������. 
������, ���� �� ����������� ������ ���� ����������� - �������������� �������� �� ������ �����.
� �������, ����� ������ (../graph/) ��������, ��� ������ ������ �� ����� �� ������� ����� � ����� ������ 
game.graph � ����� graph.

===[��������� ������]===
�������:  acdc [-c dir] [-o outfile] [-l] [-idx index_file]

-c <dir> - �����, � ������� ����� ������������� �����. ���� ��������� � ������� �����, <dir> �� �����.
-o <outfile> - ��� ��������������� ������. ���� �� ������ - new.spawn.
-l - ���� ��� ���������� level.spawn
-idx <index_file> - � ���� ������ ������ ���������� ltx ������ � �������� ����:

[box_wood_01_0021]
id = 2907
story_id = -1

�������, ���� �� ������ �������� �������� �� �� ������� �������, � �� ��� �����.
���� ������� ���� -idx ��� ���� �� �������, �� �������� � ����� � acdc (spawn_ids).

������ ������� - � ������������� ������ ��������� ��� ������ ������ ����� 'index' (������ - [24]:index),
����� ��� ���������� ������ ������ � ������-���� ������� ��������� ������ ����

[spawn_id]
name = <current_index> ; ������������ ����� � �������� id ������� � ������.

����� �������, ����� ����� �������� � ����� ������_����� ����� �� ����. ��� ���������� ������ ������
�� ������_���� ���� ����� ��������, � ����� 'index' �������������.
��� ������� ����� � ������ � ��� ������� ���������� ��� ����� -idx, ������������� ��� (spawn_ids.log), 
� ������� ����� ����������� ��� '����������' ������.

===[��������������� ������]===
�������:  acdc -convert <location> [-game1 game1,<old_gvid0>] [-game2 <game2>,<new_gvid0>] [-way]

<location> - �������� �������, ��� ������� �������������� �����. ��� ����������� ������ ���� ������� �� all.spawn 
������� all.

-game1 - ������� ������ ������ ������ � ������� <���� ������ ������>,<������ ��������� game_vertex_id �������>.
����������� - �������, ��� ��������!
-game2 - ������� ����� ������ ������ � ������� <���� ����� ������>,<����� ��������� game_vertex_id �������>.
����������� - �������, ��� ��������!
-way - ���������� ��������� ����� ������������ way.

����� �������������� ������ ��������� ����������� ����� ���� convert.ini. � ������ sections ���� ��� ���������:
to_exclude � to_change. � �������� �������� to_exclude ������������� ����� ������, ������� ���������� ������� ��� 
����������� (��������, respawn �� ����� ��� �������� � ��). � �������� �������� to_change ������������� 
section_name ��� ������, � ������� ����� ���-�� �������� ��� ���������. ����� ���������� ���� �������� ��� ��� 
section_name, ������� �� ��������� � to_change. ������:

[inventory_box]			//section_name ��� ������ ������
add:custom_data = PREVED	//������� add ������������ ��� ��� ����������, � ������� ����� ��������
add:game_vertex_id = 10000	//����������� �������� (���� ����� - ������������, ���� ������ - ����������� � �����)
rep:level_vertex_id = 0		//������� rep ������������ ��� ����������, ������� ���������� �������� �� ���-��

������: acdc -convert escape -game1 cs4,472 -game2 cop,934 -way

������ ������ ������:

-soc1 - ��, ������� �� 2�� �����, � ����� ���� 3120
-cs0 - ������� ��
-cs3 - 3 ���� ��
-cs4 - 4 ���� �� � ����
-cop - �� (����� ����)

===[�������� ������ ���������]===
�������:  acdc -parse <location> [-game1 <old_gvid0>] [-game2 <new_gvid0>] [-way]

<location> - ��� ltx, � ������� ��������� �����.
-game1 - ������� ������� ���������� game_vertex_id �������.
-game2 - ������� ������ ���������� game_vertex_id �������.
-way - ���������� ��������� ����� ������������ way.

������: acdc -parse alife_l01_escape.ltx -game1 0 -game2 934 -way

===[�������� ������ �� level.spawn]===
�������������:   acdc_cop -d *.spawn [-split_spawns] [-scan <scan_dir>]

�����:
-split_spawns - ������ all.spawn �� level.spawn � level.game ��� ������� ������. ACDC ������ ������ 
� ����� gamedata/spawns, ������ � ����� gamedata/levels ������ ������ ������������ � ������ ������, ��� ���� ��
level.spawn �� ���. ������ �������� ������ level.spawn � level.game ��� *bak �����, � ������� �� �� ����� �����.
����������� ������ ������� - ����������� ������������ ����� ����-�������.

======================================
	

������� ������:
23 ��������: 
	[i] ���������� �������������� ��� ��������� ������ ��� ����� -idx. ����� ���������, ��� ����, 
������ �������������� ����������� (����� RedPython)
	[i] ������ sections.ini ������� ����� (��-�� ���������� �������� ������������) ��������� ��� 
��������� ������������ (Artos)
	[i] ������������ ���� � �������� ������ ������������ ��� ������������ (Artos)
	[i] ���������� data_packet::unpack, ��� ��� ������ ������ ����� �������� �������. � acdc �������� 
������� �� ������ "reading vertices...".
	[i] ��������� ������ graph ��� ������� ��������������� perl-��������. � ���������� ����� ���������, 
������ ������������, ��� �� ������ ������� acdc �������� ���������.
19 �������� 2011:
	[+] ������ ��������� ��������� �����.
	[+] ��������� ������� �������� all.spawn �� level.spawn � level.game.
	[i] ���������� ����������/��������� level.spawn, ���������� � �����-�� �� ������.

18 �������� 2011:
	[+] ��������� ��������� ����� ��� ������ �������� � ������_����.
	[+] ��������� ������� ������������� ������� � ��������� �������� � �������� � �� ������.
	[+] ��������� ��������� �����-��������� ��� ������� ���������� �������������� ������ � 
alife_...ltx.

17 �������� 2011:
	[+] ��������� ����������� ���������� �� �����.
	[+] ��������� ����������� ������� ���� �� game.graph.

30 ������� 2011:
	[i] ��������� �������� ������������ ��������.
	[i] ��������� ��������� ������ NLC6.

26 ���� 2011:
	[i] ���������� ������ ������.
	[i] ���� -2942 ������ �� �������������� - acdc ������ ������������� ������������ �������� ���������� ��� 
	�������	����� ��.

25 ���� 2011:
	[+] �������� game.graph ������� � ��������� ������.
	[+] ��� ������ ���������� �� ����� ����� ��������� ������ ������������ "died on line ..."
	[i] ���������� ���������� ������� ������ 2212-2218 (����� 'no such level for vertice').
	[i] ���������� ���������� ������� ����� 2232 (����� �� m_rat_e).
	[i] ���������� ���������� ������ ����� 1902.

11 ���� 2011
	[+] �������� ����� �����-��������� ��� ������� ��������� ������� ��������.
 	[i] ���������� ���������� ��������� ���-�������.

20 ���� 2011
	[i] ������ � ���������������� ������ ������ ����������� �� �������� ������������ section_name

19 ���� 2011
	[+] �������� ���������������� ���� ��� ������ ��������� ����������� ������.
	[i] ������������ ������� ����������� ������. ��������� �������������� ����������� �� �� � ����� �������
������.

9 ���� 2011
	[+] ��������� ��������� ������� �����.
	[i] ���������� ����������� ������ m_rat_e ��� ������������� ����� ������ � ��������.

7 ���� 2011
	[i] ���������� ������ ���������� � ��������� ���� ������.

23 ��� 2011
	[i] ���������� ��������� ������ ������ �����.

18 ��� 2011
	[+] ��������� ��������� ���������� � ����� ������.

17 ��� 2011
	[i] ���������� stkutils, � ������� ������ ������ ������ �� �������� acdc
	[+] ��������� ������� �������� ������ ��������� � ������������� ������
	[+] ��������� ������� ����������� �������������� ������� � ������ �� ����������� �����. 
������ ������� ����� � level.pm

15 ��� 2011
	[i] ���������� ���������� ��������� level.spawn �� �������� ����� ��.
================================================================
���������:
ACDC ��� �� - bardak, ��� �� - bardak, Kolmogor. ��� ��������� - K.D.
�����������/������������ ��� � ��� ������, � ��������� �������.