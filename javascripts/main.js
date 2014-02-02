var app = angular.module('gbApp', ["ngRoute"]);

app.controller('MainCntl', function($scope, $route, $routeParams, $location) {
  $scope.$route = $route;
  $scope.$location = $location;
  $scope.$routeParams = $routeParams;
});

app.config(function ($routeProvider) {
  $routeProvider
    .when('/intro',
    {
      templateUrl: "contents/intro.html"
    }
  )

  $routeProvider
    .when('/kernels',
    {
      templateUrl: "contents/kernels.html"
    }
  )

  $routeProvider
    .when('/todo',
    {
      templateUrl: "contents/todo.html"
    }
  )

  $routeProvider
    .when('/kernels/:kernel',
    {
      templateUrl: "contents/urlRouter.html",
      controller: 'RouteCntl'
    }
  )

  $routeProvider.otherwise({redirectTo: '/intro'});
});

function MainCntl($scope, $route, $routeParams, $location) {
  $scope.$route = $route;
  $scope.$location = $location;
  $scope.$routeParams = $routeParams;
}

function RouteCntl($scope, $routeParams) {
  $scope.templateUrl = 'contents/kernels/'+$routeParams.kernel;
}