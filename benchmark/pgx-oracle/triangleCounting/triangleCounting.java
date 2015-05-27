/*
This class is from Oracle PGX core demo and adjusted slightly.
*/
import static oracle.pgx.api.algorithms.Argument.createGraphArg;

import java.util.List;
import java.util.Map;

import java.io.File;
import oracle.pgx.api.*;
import oracle.pgx.api.algorithms.*;
import oracle.pgx.config.*;
import oracle.pgx.common.types.PropertyType;
import oracle.pgx.api.algorithms.Argument;
import oracle.pgx.api.admin.*;

public class triangleCounting {

  public static void main(String[] argv) throws Exception {

    if (argv.length != 1) {
      System.err.println("usage: " + triangleCounting.class.getName() + " <graph config path>");
      System.exit(-1);
    }
    GraphConfig cfg = GraphConfigFactory.forAnyFormat().fromPath(argv[0]);

    String sessionId = null;
    Core core = null;
    try {
      core = Pgx.getCore();
      sessionId = core.createSession("my-session").get();
      LoadingResult graph = core.loadGraphWithProperties(sessionId, cfg).get();
      String graphName = graph.getGraphName();

      { // triangle counting
        List<String> result = core.createUndirectedGraph(sessionId, graphName, null, false, false, false, false, null).get();
        String undirectedGraphName = result.get(0);
        String triangleCounting = BuiltinAlgorithms.Type.PGX_BUILTIN_S1_TRIANGLE_COUNTING.getAnalysisName();
        Argument[] args = new Argument[] { createGraphArg(undirectedGraphName) };
        InvocationResult<Long> ir = core.runAnalysis(sessionId, triangleCounting, args, Long.class).get();
        if (ir.isSuccess()) {
          long triangles = ir.getReturnValue();
          System.out.println(triangles + " triangles computed in " + ir.getExecutionTimeMs() + " milliseconds");
        } else {
          ir.getException().printStackTrace();
        }
      }

    } finally {

      Control ctrl = Pgx.getControl();
      if (ctrl.isRunning()) {
        if (sessionId != null) {
          core.destroySession(sessionId).get();
        }
        ctrl.shutdownNow();
      }
    }
  }

}
