#! /usr/bin/awk -f

BEGIN {
	rtn = 1
	count = 1
}
{
	while(rtn == 1) {
		if(substr($0,1,1) == "#" || substr($0,1,1) == "-" || $0 == "") {
			print $0					# comment
			rtn = getline
		} else if(index($0, "./tq.o") == 0) {			# usual comand
				system($0);
				rtn = getline
		} else {						# tq

			printf "[%04d] %s\n", count, $0			# command

			tq_result = sprintf("xxx_%04d.tq", count)	# tq result path
			i = match($0, /##* /)                           # comment after command   eg. "./tq.o -h  ### help"
			if(i>0) {
				com = substr($0, 1, i-1)
			} else {
				com = $0
			}

			tq_command = sprintf("%s > %s", com, tq_result)
			system(tq_command) 				# exec tq

			sub("./tq.o", "./cq.o", com) 
			cq_result = sprintf("xxx_%04d.cq", count)	# cq result path
                	cq_command = sprintf("%s > %s", com, cq_result)
                	system(cq_command)				# exec cq

			printf "<tq/cq> "
			diff = sprintf("diff -s %s %s", tq_result, cq_result)     # tq vs cq diff
			system(diff)

			rtn = getline
			if(rtn == 1 && substr($0, 1, 3) == " =>") {			# answer follows

				answer = sprintf("xxx_%04d.ans", count)	# anser path

				if($0 == " =>" || $0 == " => ") {
					rtn = getline
					print $0 > answer		# expected answer (1st line)
					getline
					while(rtn == 1 && ($0 != "###end")) {
						print $0 >> answer		# expected answer (following lines)
						getline
					}
				} else {		# answer follows
					print substr($0, 5) > answer		# expected answer (1st line)
				} 

				printf "<tq/ans> "
				diff = sprintf("diff -s %s %s", tq_result, answer)	# exec diff
				system(diff)

				rtn = getline

			}

			printf "\n\n"
			count++
		}

	}
}
