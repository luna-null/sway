#include <wlr/util/log.h>
#include "sway/input/input-manager.h"
#include "sway/input/seat.h"
#include "sway/view.h"
#include "sway/commands.h"

struct cmd_results *cmd_kill(int argc, char **argv) {
	if (!config->handler_context.current_container) {
		wlr_log(L_ERROR, "cmd_kill called without container context");
		return cmd_results_new(CMD_INVALID, NULL,
				"cmd_kill called without container context "
				"(this is a bug in sway)");
	}
	// TODO close arbitrary containers without a view
	struct sway_view *view =
		config->handler_context.current_container->sway_view;

	if (view && view->iface.close) {
		view->iface.close(view);
	}

	return cmd_results_new(CMD_SUCCESS, NULL, NULL);
}
