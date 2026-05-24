/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_launcher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/24 14:28:02 by alerusso          #+#    #+#             */
/*   Updated: 2026/05/24 14:55:31 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tests.h"

int	signals_launcher(void)
{
	t_test_list	list;

	list = (t_test_list){0};
	load_test(&list, "sigsegv_test", sig_01_segv);
	load_test(&list, "sigbus_test", sig_02_bus);
	load_test(&list, "sigalrm_test", sig_03_alrm);
	load_test(&list, "sigabrt_test", sig_04_abrt);
	load_test(&list, "sigfpe_test", sig_05_fpe);
	load_test(&list, "sigpipe_test", sig_06_pipe);
	load_test(&list, "sigill_test", sig_07_ill);
	return (launch_tests(&list, "SIGNALS"));
}
