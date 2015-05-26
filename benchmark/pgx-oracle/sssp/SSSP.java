/*
This class is written following the format in the Oracle PGX core demo
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

public class SSSP {

  public static void main(String[] argv) throws Exception {

    if (argv.length != 4) {
      System.err.println("usage: " + SSSP.class.getName() + " <graph config path>"
                          + " <costPropName in the .json file> " + "<src node name>" 
                          + "<dest node name>");
      System.exit(-1);
    }
    // GraphConfig cfg = GraphConfig.fromPath(argv[0]);
    GraphConfig cfg = GraphConfigFactory.forAnyFormat().fromPath(argv[0]);
    String sessionId = null;
    Core core = null;
    try {
      core = Pgx.getCore();
      sessionId = core.createSession("my-session").get();
      LoadingResult graph = core.loadGraphWithProperties(sessionId, cfg).get();
      String graphName = graph.getGraphName();

      {
        String parentName = core.createNodeProperty(sessionId, graphName, PropertyType.NODE).get();
        String parentEdgeName = core.createNodeProperty(sessionId, graphName, PropertyType.EDGE).get();
        String sssp = BuiltinAlgorithms.Type.PGX_BUILTIN_P1a_SINGLE_SOURCE_SINGLE_DESTINATION_DIJKSTRA.getAnalysisName();
        Argument[] args = new Argument[] {
          Argument.createGraphArg(graphName), 
          Argument.createEdgePropertyArg(argv[1]),
          Argument.createNodeIdInArg(Integer.parseInt(argv[2])),
          Argument.createNodeIdInArg(Integer.parseInt(argv[3])),
          Argument.createNodePropertyArg(parentName),
          Argument.createNodePropertyArg(parentEdgeName)
        };

        InvocationResult<Boolean> ir = core.runAnalysis(sessionId, sssp, args, Boolean.class).get();
        if (ir.isSuccess()) {
          Boolean result = ir.getReturnValue();
          System.out.println("SSSP computed in " + ir.getExecutionTimeMs() + " milliseconds");
          if (result) {
            System.out.println("There is a path between " + Integer.parseInt(argv[2]) + " and " + Integer.parseInt(argv[3]));
          } else {
            System.out.println("There is not a path between " + Integer.parseInt(argv[2]) + " and " + Integer.parseInt(argv[3]));
          }
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
