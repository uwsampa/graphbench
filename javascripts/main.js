angular.module('gbApp', []).
    config(function ($routeProvider) {
        $routeProvider.when('/:primaryNav', {
            templateUrl: 'index.html',
            controller: 'RouteController'
        });
    });

function RouteController($scope, $routeParams) {
		if ($routeParams.primaryNav) {
			$scope.page = $routeParams.primaryNav;
		} else {
			$scope.page = 'intro';
		}
		
    }